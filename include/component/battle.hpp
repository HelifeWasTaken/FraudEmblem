#include "components/sprite.h"
#include "components/animator.h"
#include "Stats.hpp"
#include "Context.hpp"
#include <fstream>

class FightScene
{
private:
    class Battler
    {
    public:
        Battler(const emblem::Stats& s)
            : stats(s) {}

        kat::Sprite sprite;
        kat::Animator *animator;
        emblem::Stats stats;
        int fought_count = 0;
        int max_fights = 2;

        sf::Vector2f target_position;
    } *left, *right;

    kat::Sprite background;
    sf::Vector2f background_position = sf::Vector2f(0, 0);

    enum {
        LEFT_FIGHTING,
        RIGHT_FIGHTING,
        NONE_FIGHTING
    } fighting = NONE_FIGHTING;

    bool ready = false;
    bool lturn = true;

    using Stats = emblem::Stats;

public:
    FightScene(const Stats& lstats,
               const std::string& left_battler,
               const Stats& rstats,
               const std::string& right_battler,
               const std::string& path_background)
    {
        this->background.create(emblem::Context::getResource<kat::Texture>(path_background));
        this->left = new Battler(lstats);
        this->right = new Battler(rstats);

        // load a json to get info about the battler animations and stuff
        {
            nlohmann::json json;
            std::ifstream file("../assets/characters/" + left_battler + ".json");

            file >> json;

            // create the sprite
            this->left->sprite.create(emblem::Context::getResource<kat::Texture>(json["texture"]));
            //this->left->sprite.setOrigin(this->left->sprite.getGlobalBounds().width / 2,
            //                            this->left->sprite.getGlobalBounds().height / 2);

            // load animations
            //this->left->sprite.setPosition(json["position_left"][0], json["position_left"][1]);
            this->left->target_position = sf::Vector2f(json["position_left"][0], json["position_left"][1]);
            this->left->animator = new kat::Animator(this->left->sprite);
            kat::FrameIndexList frames;

            for (auto& frame : json["animations"]["idle"]["frames"])
                frames.push_back(frame);

            this->left->animator->addAnimationSpritesheet(
                "idle",
                frames,
                kat::FrameSize(json["size"][0], json["size"][1]),
                json["animations"]["idle"]["speed"]
            );
            frames.clear();

            for (auto& frame : json["animations"]["attack"]["frames"]) {
                frames.push_back(frame);
                std::cout << frame << std::endl;
            }

            this->left->animator->addAnimationSpritesheet(
                "attack",
                frames,
                kat::FrameSize(json["size"][0], json["size"][1]),
                json["animations"]["attack"]["speed"],
                false
            );
            this->left->sprite.setPosition(
                left->target_position.x + (float)json["size"][0],
                -500);

            this->left->animator->playAnimation("idle");
        }

        {
            nlohmann::json json;
            std::ifstream file("../assets/characters/" + right_battler + ".json");
            file >> json;

            // create the sprite
            this->right->sprite.create(emblem::Context::getResource<kat::Texture>(json["texture"]));
            //this->right->sprite.setOrigin(this->right->sprite.getGlobalBounds().width / 2,
            //                            this->right->sprite.getGlobalBounds().height / 2);

            // load animations
            //this->left->sprite.setPosition(json["position_left"][0], json["position_left"][1]);
            this->right->target_position = sf::Vector2f(json["position_right"][0], json["position_right"][1]);
            this->right->animator = new kat::Animator(this->right->sprite);
            kat::FrameIndexList frames;

            for (auto& frame : json["animations"]["idle"]["frames"])
                frames.push_back(frame);

            this->right->animator->addAnimationSpritesheet(
                "idle",
                frames,
                kat::FrameSize(json["size"][0], json["size"][1]),
                json["animations"]["idle"]["speed"]
            );
            frames.clear();

            for (auto& frame : json["animations"]["attack"]["frames"])
                frames.push_back(frame);

            this->right->animator->addAnimationSpritesheet(
                "attack",
                frames,
                kat::FrameSize(json["size"][0], json["size"][1]),
                json["animations"]["attack"]["speed"],
                false
            );
            //this->left->max_fights = json["max_fights"];
            this->right->sprite.setPosition(right->target_position.x, -500);
            this->right->animator->playAnimation("idle");
        }
        this->background.setPosition(background_position.x, -500);

        this->right->max_fights = 5;
    }

    ~FightScene()
    {
        delete left;
        delete right;
    }

    // Returns false if the fight is over
    bool update(float dt)
    {
        left->animator->update(dt);
        right->animator->update(dt);

        if (!ready) {
            if (left->sprite.getPosition().y < left->target_position.y) {
                left->sprite.move(0, 500 * dt);
            }
            if (right->sprite.getPosition().y < right->target_position.y) {
                right->sprite.move(0, 500 * dt);
            }
            if (background.getPosition().y < 0) {
                background.move(0, 500 * dt);
            }
            if (left->sprite.getPosition().y >= left->target_position.y &&
                right->sprite.getPosition().y >= right->target_position.y &&
                background.getPosition().y >= background_position.y) {
                ready = true;
            } else {
                return true;
            }
        }

        if (fighting == NONE_FIGHTING) {
            if (lturn) {
                if (left->fought_count < left->max_fights) {
                    left->animator->playAnimation("attack");
                    right->animator->playAnimation("idle");
                    fighting = LEFT_FIGHTING;
                } else if (right->fought_count < right->max_fights) {
                    right->animator->playAnimation("attack");
                    left->animator->playAnimation("idle");
                    fighting = RIGHT_FIGHTING;
                } else {
                    right->animator->playAnimation("idle");
                    left->animator->playAnimation("idle");
                    return false;
                }
            } else {
                if (right->fought_count < right->max_fights) {
                    right->animator->playAnimation("attack");
                    left->animator->playAnimation("idle");
                    fighting = RIGHT_FIGHTING;
                } else if (left->fought_count < left->max_fights) {
                    left->animator->playAnimation("attack");
                    right->animator->playAnimation("idle");
                    fighting = LEFT_FIGHTING;
                } else {
                    right->animator->playAnimation("idle");
                    left->animator->playAnimation("idle");
                    return false;
                }
            }
        } else if (fighting == LEFT_FIGHTING) {
            if (!left->animator->isPlaying()) {
                right->stats.damage(left->stats.atk);
                left->fought_count++;
                fighting = NONE_FIGHTING;
                lturn = false;
            }
        } else if (fighting == RIGHT_FIGHTING) {
            if (!right->animator->isPlaying()) {
                left->stats.damage(right->stats.atk);
                right->fought_count++;
                fighting = NONE_FIGHTING;
                lturn = true;
            }
        }
        return true;
    }

    std::pair<Stats, Stats> getStats() const
    {
        return {left->stats, right->stats};
    }

    void draw(emblem::Window &w)
    {
        this->left->animator->flipX(true);
        w.draw(background, "fight");
        w.draw(left->sprite, "fight");
        w.draw(right->sprite, "fight");
    }
};