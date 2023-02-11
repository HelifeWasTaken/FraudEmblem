#pragma once

#include "sprite.h"
#include <unordered_map>

namespace kat {

    // Fwd
    struct Animation;

    /**
     * @brief A list of frames for an animation.
     */
    using FrameList = std::vector<Frame>;

    /**
     * @brief The time each frame of an animation is displayed.
     */
    using FrameTime = float;

    /**
     * @brief An animation name.
     */
    using AnimationName = std::string;

    /**
     * @brief A mapping of animation names to Animation objects.
     */
    using AnimationRegistry = std::unordered_map<AnimationName, Animation>;

    /**
     * @brief A frame index.
     */
    using FrameIndex = u32;

    /**
     * @brief A list of frame indices.
     */
    using FrameIndexList = std::vector<FrameIndex>;

    /**
     * @brief Represents a single animation.
     */
    struct Animation {
        FrameList frames;         ///< The list of frames in the animation.
        FrameTime speed = 0.2; ///< The time each frame is displayed.
        bool loop = true;         ///< Whether the animation should loop.

        bool flipX = false;       ///< Whether the animation should be flipped on the X axis.
        bool flipY = false;       ///< Whether the animation should be flipped on the Y axis.

        /**
         * @brief Default constructor.
         */
        Animation() = default;

        /**
         * @brief Destructor.
         */
        ~Animation() = default;

        /**
         * @brief Add a single frame to the animation.
         * @param frame The frame to add.
         */
        void addFrame(const Frame& frame);

        /**
         * @brief Add a list of frames to the animation.
         * @param frames The list of frames to add.
         */
        void addFrames(const FrameList& frames);

        /**
         * @brief Set the time each frame is displayed.
         * @param frame_time The time to display each frame.
         */
        void setSpeed(const FrameTime& frame_time);

        /**
         * @brief Set whether the animation should loop.
         * @param loop Whether the animation should loop.
         */
        void setLoop(const bool& loop);

        /**
         * @brief Set whether the animation should be flipped on the X axis.
         * @param flip Whether the animation should be flipped on the X axis.
         */
        void setFlipX(const bool& flip);

        /**
         * @brief Set whether the animation should be flipped on the Y axis.
         * @param flip Whether the animation should be flipped on the Y axis.
         */
        void setFlipY(const bool& flip);
    };

    /**
     * @brief The possible states of an animation.
     */
    enum class AnimationState {
        Playing, ///< The animation is currently playing.
        Stopped  ///< The animation is stopped.
    };

    /**
     * @brief The possible looping modes for an animation.
     */
    enum class AnimationLoop {
        Default,  ///< Use the default looping mode set in the Animation object.
        Loop,     ///< Loop the animation.
        NoLoop    ///< Do not loop the animation.
    };

    /**
     * @brief A class for animating a sprite using a set of Animation objects.
     */
    class Animator {
    private:
        Sprite m_sprite; ///< The sprite being animated.
        AnimationRegistry m_animations; ///< The set of available animations.
        AnimationState m_playing = AnimationState::Stopped; ///< Whether an animation is currently playing.
        bool m_loop = false; ///< Whether the current animation should loop.
        FrameTime m_frame_time = 0.0f; ///< The time each frame is displayed.
        FrameIndex m_frame_index = 0; ///< The index of the current frame in the current animation.
        Animation *m_current_animation = nullptr; ///< A pointer to the current animation.

        /**
        * @brief Set the current animation to the default animation.
        */
        void _defaultAnimation();

    public:
        /**
         * @brief Construct an Animator with a reference to a sprite.
         * @param sprite The sprite to animate.
         */
        Animator(Sprite& sprite);

       /**
        * @brief Construct an Animator with a reference to a sprite and a set of animations.
        * @param sprite The sprite to animate.
        * @param animations The set of available animations.
        */
        Animator(Sprite& sprite, AnimationRegistry& animations);

       /**
        * @brief Destructor.
        */
        ~Animator() = default;

       /**
        * @brief Add an animation to the set of available animations.
        * @param name The name of the animation.
        * @param animation The animation object.
        * @return A reference to the Animator object.
        */
        Animator& addAnimation(const AnimationName& name, const Animation& animation);

        Animation &getAnimation(const AnimationName &name);

       /**
        * @brief Remove an animation from the set of available animations.
        * @param name The name of the animation to remove.
        * @return A reference to the Animator object.
        */
        Animator& removeAnimation(const AnimationName& name);

       /**
        * @brief Play an animation.
        * @param name The name of the animation to play.
        * @param loop The looping mode for the animation.
        * @return A reference to the Animator object.
        */
        Animator& playAnimation(const AnimationName& name, const AnimationLoop& loop = AnimationLoop::Default);

        /**
         * @brief Play an animation but does not restart the animation if it is already playing.
         * @param name The name of the animation to play.
         * @param loop Whether the animation should loop.
         * @return A reference to the Animator object.
         */
        Animator& play(const AnimationName& name, const AnimationLoop &loop = AnimationLoop::Default);

       /**
        * @brief Stop the current animation.
        * @return A reference to the Animator object.
        */
        Animator& stopAnimation();

       /**
        * @brief Update the sprite's texture to the current frame of the current animation.
        * @param dt The elapsed time since the last update.
        * @return A reference to the Animator object.
        */
        Animator& update(const FrameTime& dt);

       /**
        * @brief Check whether an animation is currently playing.
        * @return true if an animation is playing, false otherwise.
        */
        bool isPlaying() const;

       /**
        * @brief Check whether the current animation is set to loop.
        * @return true if the current animation is set to loop, false otherwise.
        */
        bool isLooping() const;

       /**
        * @brief Add an animation created from a spritesheet to the set of available animations.
        * @param name The name of the animation.
        * @param frames The list of frames in the animation.
        * @param frame_size The size of each frame in the spritesheet.
        * @param texture_size The size of the texture containing the spritesheet.
        * @param frame_time The time to display each frame.
        * @param loop Whether the animation
        * @return A reference to the Animator object.
        */
        Animator& addAnimationSpritesheet(
            const AnimationName& name,
            const FrameIndexList& frames,
            const FrameSize& frame_size,
            const FrameTime& frame_time,
            const TextureSize& texture_size,
            const bool& loop = true);

         /**
          * @brief Add an animation created from a spritesheet to the set of available animations.
          *        It is assumed that the texture containing the spritesheet is the same size as
          *        the spritesheet.
          * @param name The name of the animation.
          * @param frames The list of frames in the animation.
          * @param frame_size The size of each frame in the spritesheet.
          * @param frame_time The time to display each frame.
          * @param loop Whether the animation
          * @return A reference to the Animator object.
          */
        Animator& addAnimationSpritesheet(
            const AnimationName& name,
            const FrameIndexList& frames,
            const FrameSize& frame_size,
            const FrameTime& frame_time,
            const bool& loop = true);

        Animator &flipX(const bool &flip);
        Animator &flipY(const bool &flip);

        bool isFlippedX() const;
        bool isFlippedY() const;

    };
}