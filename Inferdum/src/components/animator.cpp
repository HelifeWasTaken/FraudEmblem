#include "Kat/components/animator.h"

namespace kat {

    void Animation::addFrame(const Frame& frame) {
        frames.push_back(frame);
    }

    void Animation::addFrames(const FrameList& pframes) {
        frames.insert(frames.end(), pframes.begin(), pframes.end());
    }

    void Animation::setSpeed(const FrameTime& pframe_time) {
        speed = pframe_time;
    }

    void Animation::setLoop(const bool& ploop) {
        loop = ploop;
    }

    void Animator::_defaultAnimation() {
        auto anim = Animation();
        const auto& tx_size = m_sprite.getTexture().size();

        anim.addFrame(Frame(0, 0, tx_size.x, tx_size.y));
        anim.setLoop(false);
        anim.setSpeed(0.0f);
        m_animations["default"] = std::move(anim);
        m_current_animation = &m_animations["default"];
    }

    Animator::Animator(Sprite& sprite)
        : m_sprite(sprite)
    {
        _defaultAnimation();
    }

    Animator::Animator(Sprite& sprite, AnimationRegistry& animations)
        : m_sprite(sprite)
        , m_animations(animations)
    {
        _defaultAnimation();
    }

    Animator& Animator::addAnimation(const AnimationName& name, const Animation& animation) {
        m_animations[name] = animation;
        return *this;
    }

    Animator& Animator::removeAnimation(const AnimationName& name) {
        m_animations.erase(name);
        return *this;
    }

    Animator& Animator::playAnimation(const AnimationName& name, const AnimationLoop& loop) {
        m_sprite.setTextureRect(m_animations[name].frames[0]);
        if (loop == AnimationLoop::Default) {
            m_loop = m_animations[name].loop;
        } else {
            m_loop = loop == AnimationLoop::Loop;
        }
        m_current_animation = &m_animations[name];
        m_playing = AnimationState::Playing;
        m_frame_time = 0.0f;
        m_frame_index = 0;
        m_sprite.setTextureRect(m_current_animation->frames[0]);
        return *this;
    }

    Animator& Animator::play(const AnimationName& name, AnimationLoop loop) {
        if (m_current_animation == &m_animations[name]) {
            if (loop == AnimationLoop::Default) {
                loop = m_animations[name].loop;
            }
            if (m_loop != loop) {
                return playAnimation(name, loop);
            }
            return *this;
        }
        return playAnimation(name, loop);
    }

    Animator& Animator::stopAnimation() {
        m_playing = AnimationState::Stopped;
        return *this;
    }

    Animator& Animator::update(const FrameTime& dt) {
        if (m_playing == AnimationState::Stopped) {
            return *this;
        }
        m_frame_time += dt;
        if (m_frame_time >= m_current_animation->speed) {
            m_frame_time -= m_current_animation->speed;
            if (m_loop == false) {
                if (m_frame_index == m_current_animation->frames.size() - 1) {
                    m_playing = AnimationState::Stopped;
                    return *this;
                }
            }
            if (++m_frame_index >= m_current_animation->frames.size()) {
                m_frame_index = 0;
            }
            m_sprite.setTextureRect(m_current_animation->frames[m_frame_index]);
        }
        return *this;
    }

    bool Animator::isPlaying() const {
        return m_playing == AnimationState::Playing;
    }

    bool Animator::isLooping() const {
        return m_loop;
    }

    Animator& Animator::addAnimationSpritesheet(
        const AnimationName& name,
        const FrameIndexList& frames,
        const FrameSize& frame_size,
        const FrameTime& frame_time,
        const TextureSize& texture_size,
        const bool& loop)
    {
        FrameList all_possible_frames;

        for (FrameIndex y = 0; y < texture_size.y; y += frame_size.y) {
            for (FrameIndex x = 0; x < texture_size.x; x += frame_size.x) {
                all_possible_frames.push_back(Frame(x, y, (int)frame_size.x, (int)frame_size.y));
            }
        }

        auto anim = Animation();
        anim.setSpeed(frame_time);
        anim.setLoop(loop);

        for (const auto& frame : frames) {
            anim.addFrame(all_possible_frames[frame]);
        }
        m_animations[name] = std::move(anim);
        return *this;
    }

    Animator& Animator::addAnimationSpritesheet(
        const AnimationName& name,
        const FrameIndexList& frames,
        const FrameSize& frame_size,
        const FrameTime& frame_time,
        const bool& loop)
    {
        return addAnimationSpritesheet(name, frames, frame_size, frame_time, m_sprite.getTexture().size(), loop);
    }
}
