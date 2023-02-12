

class FightScene
{
private:
    struct Battler
    {
        kat::Sprite sprite;
        kat::Animator *animator;
        Stats stats;
        int fought_count = 0;
        int max_fights = INT_MAX;

        sf::Vector2f target_position;
    } *left, *right;

    paa::Sprite background;
    sf::Vector2f background_position = sf::Vector2f(50, 250);
    
    enum {
        LEFT_FIGHTING,
        RIGHT_FIGHTING,
        NONE_FIGHTING
    } fighting = NONE_FIGHTING;

    bool ready = false;

public:
    FightScene(const Stats& lstats,
               const std::string& left_battler,
               const Stats& rstats,
               const std::string& right_battler,
               const std::string& background)
    {
        this->background.create(background);
        this->left = new Battler();
        this->right = new Battler();
        this->left->stats = lstats;
        this->right->stats = rstats;

        // load a json to get info about the battler animations and stuff
        {
            nlohmann::json json;
            std::ifstream file("assets/battlers/" + left_battler + ".json");
            file >> json;

            // create the sprite
            this->left->sprite.create(json["texture"]);
            this->left->sprite.setOrigin(this->left->sprite.getGlobalBounds().width / 2,
                                        this->left->sprite.getGlobalBounds().height / 2);

            // load animations
            //this->left->sprite.setPosition(json["position_left"][0], json["position_left"][1]);
            this->left->target_position = sf::Vector2f(json["position_left"][0], json["position_left"][1]);
            this->left->animator = new kat::Animator(this->left->sprite);
            this->left->animator->addAnimationSpritesheet(
                "idle",
                json["animations"]["idle"]["frames"],
                json["animations"]["size"],
                json["animations"]["idle"]["speed"]
            );
            this->left->animator->addAnimationSpritesheet(
                "attack",
                json["animations"]["attack"]["frames"],
                json["animations"]["size"],
                json["animations"]["attack"]["speed"],
                false
            );
            this->left->animator->flipX(true);
            //this->left->max_fights = json["max_fights"];
        }

        {
            nlohmann::json json;
            std::ifstream file2("assets/battlers/" + right_battler + ".json");
            file2 >> json;

            // create the sprite
            this->right->sprite.create(json["texture"]);
            this->right->sprite.setOrigin(this->right->sprite.getGlobalBounds().width / 2,
                                        this->right->sprite.getGlobalBounds().height / 2);
            //this->right->sprite.setPosition(json["position_right"][0], json["position_right"][1]);
            this->right->target_position = sf::Vector2f(json["position_right"][0], json["position_right"][1]);

            // load animations
            this->right->animator = new kat::Animator(this->right->sprite);
            this->right->animator->addAnimationSpritesheet(
                "idle",
                json["animations"]["idle"]["frames"],
                json["animations"]["size"],
                json["animations"]["idle"]["speed"]
            );
            this->right->animator->addAnimationSpritesheet(
                "attack",
                json["animations"]["attack"]["frames"],
                json["animations"]["size"],
                json["animations"]["attack"]["speed"],
                false
            );

            // set the max fights
            this->right->max_fights = json["max_fights"];
        }

        this->left->sprite.setPosition(left->target_position.x, -500);
        this->right->sprite.setPosition(right->target_position.x, -500);
        this->background.setPosition(background_position.x, -500);
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
            if (left->fought_count < left->max_fights) {
                left->animator->play("attack");
                right->animator->play("idle");
                fighting = LEFT_FIGHTING;
            } else if (right->fought_count < right->max_fights) {
                right->animator->play("attack");
                left->animator->play("idle");
                fighting = RIGHT_FIGHTING;
            } else {
                return false;
            }
        } else if (fighting == LEFT_FIGHTING) {
            if (!left->animator->isPlaying()) {
                right->stats.damage(left->stats.atk);
                left->fought_count++;
                fighting = NONE_FIGHTING;
            }
        } else if (fighting == RIGHT_FIGHTING) {
            if (!right->animator->isPlaying()) {
                left->stats.damage(right->stats.atk);
                right->fought_count++;
                fighting = NONE_FIGHTING;
            }
        }
    }

    std::pair<Stats, Stats> getStats() const
    {
        return {left->stats, right->stats};
    }


};