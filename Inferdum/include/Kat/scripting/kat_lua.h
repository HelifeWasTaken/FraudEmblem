#include "sol/sol.hpp"

#include "../batch.h"
#include "../components.h"
#include "../input.h"
#include "../math.h"
#include "../meta.h"
#include "../resource.h"
#include "../version.h"
#include "../window.h"

namespace kat {

    class Lua {
    private:
        sol::state m_state;
        sol::table m_kat;

        template<typename T>
        Lua& generate_vec2(const std::string& name) {
            m_kat.new_usertype<Vector2<T>>(name,
                sol::constructors<Vector2<T>(), Vector2<T>(T, T)>(),
                "x", &Vector2<T>::x,
                "y", &Vector2<T>::y
            );
            return *this;
        }

        template<typename T>
        Lua& generate_vec3(const std::string& name) {
            m_kat.new_usertype<Vector3<T>>(name,
                sol::constructors<Vector3<T>(), Vector3<T>(T, T, T)>(),
                "x", &Vector3<T>::x,
                "y", &Vector3<T>::y,
                "z", &Vector3<T>::z
            );
            return *this;
        }

        template<typename T>
        Lua& generate_rect(const std::string& name) {
            m_kat.new_usertype<Rect<T>>(name,
                sol::constructors<Rect<T>(), Rect<T>(T, T, T, T)>(),
                "left", &Rect<T>::top,
                "top", &Rect<T>::left,
                "x", &Rect<T>::left,
                "y", &Rect<T>::top,
                "width", &Rect<T>::width,
                "height", &Rect<T>::height
            );
            return *this;
        }

        void load_basic_vector_types()
        {
            generate_vec2<u8>("Vector2u8").generate_vec2<i8>("Vector2i8")
                .generate_vec2<u16>("Vector2u16").generate_vec2<i16>("Vector2i16")
                .generate_vec2<u32>("Vector2u").generate_vec2<i32>("Vector2i")
                .generate_vec2<u64>("Vector2u64").generate_vec2<i64>("Vector2i64")
                .generate_vec2<f32>("Vector2f").generate_vec2<f64>("Vector2d")
                .generate_vec3<u8>("Vector3u8").generate_vec3<i8>("Vector3i8")
                .generate_vec3<u16>("Vector3u16").generate_vec3<i16>("Vector3i16")
                .generate_vec3<u32>("Vector3u").generate_vec3<i32>("Vector3i")
                .generate_vec3<u64>("Vector3u64").generate_vec3<i64>("Vector3i64")
                .generate_vec3<f32>("Vector3f").generate_vec3<f64>("Vector3d");
        }

        void load_basic_rect_types()
        {
            generate_rect<u8>("Rectu8").generate_rect<i8>("Recti8")
                .generate_rect<u16>("Rectu16").generate_rect<i16>("Recti16")
                .generate_rect<u32>("Rectu32").generate_rect<i32>("IntRect")
                .generate_rect<u64>("Rectu64").generate_rect<i64>("Recti64")
                .generate_rect<f32>("FloatRect");
        }

        void load_window_api()
        {
            m_kat.new_usertype<ContextSettings>("ContextSettings",
                sol::constructors<ContextSettings()>(),
                "depthBits", &ContextSettings::depthBits,
                "stencilBits", &ContextSettings::stencilBits,
                "antialiasingLevel", &ContextSettings::antialiasingLevel,
                "majorVersion", &ContextSettings::majorVersion,
                "minorVersion", &ContextSettings::minorVersion,
                "attributeFlags", &ContextSettings::attributeFlags
            );

            m_kat["ContextAttribute::Default"] = ContextAttribute::Default;
            m_kat["ContextAttribute::Core"] = ContextAttribute::Core;
            m_kat["ContextAttribute::Debug"] = ContextAttribute::Debug;

            m_kat.new_usertype<VideoMode>("VideoMode",
                sol::constructors<VideoMode(), VideoMode(const Vector2<u32>&, u32)>(),
                "size", &VideoMode::size,
                "bitsPerPixel", &VideoMode::bitsPerPixel
            );

            m_kat["WindowStyle::None"] = WindowStyle::None;
            m_kat["WindowStyle::Titlebar"] = WindowStyle::Titlebar;
            m_kat["WindowStyle::Resize"] = WindowStyle::Resize;
            m_kat["WindowStyle::Close"] = WindowStyle::Close;
            m_kat["WindowStyle::Fullscreen"] = WindowStyle::Fullscreen;
            m_kat["WindowStyle::Default"] = WindowStyle::Default;

            generate_rect<u32>("WindowSize");
        }

        void load_resource_api()
        {
            m_kat.new_usertype<ResourceManager>("ResourceManager",
                sol::constructors<ResourceManager()>(),
                "loadTextureFromFile",
                [](ResourceManager& self, const std::string& path, const std::string& name) {
                    self.addResource(name, Texture().load(path));
                    return self;
                },
                "loadTexture",
                [](ResourceManager& self, const Texture& texture, const std::string& name) {
                    self.addResource(name, texture);
                    return self;
                },
                "getTexture",
                [](ResourceManager& self, const std::string& name) {
                    return self.getResource<Texture>(name);
                }
            );
        }

        void load_texture_component()
        {
            generate_rect<i32>("Frame");
            generate_vec2<u32>("TextureSize");
            generate_vec2<u32>("TextureSize");
            generate_vec2<f32>("Position");

            m_kat.new_usertype<Texture>("KatTexture",
                sol::constructors<Texture()>(),
                "loadFromFile", [](Texture& self, const std::string& path)
                { return self.load(path); },

                "copyTexture", [](Texture& self, const Texture& other_texture)
                { return self.load(other_texture); },

                "loadFromMemory", [](Texture& self, const void *data, u64 size)
                { return self.load((Memory)data, size); },

                "windowToTexture", [](Texture& self, Window& window) {
                    if (self.size() == TextureSize(0, 0)) {
                        self.create(TextureSize(window.size().x, window.size().y));
                    }
                    self.update(window);
                    return self;
                },
                "setSmooth", &Texture::setSmooth,
                "isSmooth", &Texture::isSmooth,

                "isRepeated", [](Texture& self) { return self.repeated(); },
                "setRepeated", [](Texture& self, bool repeated) { self.repeated(repeated); return self; }
            );
        }

        void load_sprite_component()
        {
            generate_vec2<f32>("Scale");

            m_kat.new_usertype<Color>("Color",
                sol::constructors<Color(), Color(u8, u8, u8), Color(u8, u8, u8, u8)>(),
                "r", &Color::r,
                "g", &Color::g,
                "b", &Color::b,
                "a", &Color::a
            );

            m_kat.new_usertype<Angle>("Angle",
                "asDegrees", &Angle::asDegrees,
                "asRadians", &Angle::asRadians
            );

            m_kat.new_usertype<Transform>("Transform",
                sol::constructors<
                    Transform(),
                    Transform(f32, f32, f32, f32, f32, f32, f32, f32, f32)
                >(),
                "getMatrix",
                [](Transform& self) {
                    const float *matrix = self.getMatrix();
                    return std::array<f32, 9> {
                        matrix[0], matrix[1], matrix[2],
                        matrix[3], matrix[4], matrix[5],
                        matrix[6], matrix[7], matrix[8]
                    };
                },

                "getInverse", &Transform::getInverse,

                "transformPoint",
                [](Transform& self, const Position& point)
                { self.transformPoint(point); return self; },

                "transformRect",
                [](Transform& self, const FloatRect& rect)
                { self.transformRect(rect); return self; },

                "combine", &Transform::combine,

                "translate", 
                [](Transform& self, const Position& offset)
                { return self.translate(offset); },

                "rotate",
                [](Transform& self, f32 angle)
                { return self.rotate(sf::degrees(angle)); },

                "rotateRad",
                [](Transform& self, f32 angle)
                { return self.rotate(sf::radians(angle)); },

                "rotateAround",
                [](Transform& self, f32 angle, const Position& center)
                { return self.rotate(sf::degrees(angle), center); },

                "rotateAroundRad",
                [](Transform& self, f32 angle, const Position& center)
                { return self.rotate(sf::radians(angle), center); },

                "scale",
                [](Transform& self, const Scale& factors)
                { return self.scale(factors); },

                "scaleAround",
                [](Transform& self, const Scale& factors, const Position& center)
                { return self.scale(factors, center); }
            );

            generate_rect<f32>("GlobalBounds");
            generate_rect<f32>("LocalBounds");

            m_kat.new_usertype<Sprite>("Sprite",
                sol::constructors<Sprite()>(),
                "create",
                [](Sprite& self, Texture& texture) {
                    return self.create(texture);
                },
                "setPosition",
                [](Sprite& self, const Position& pos) {
                    return self.setPosition(pos);
                },
                "setRotation",
                [](Sprite& self, f32 angle) {
                    return self.setRotation(sf::degrees(angle));
                },
                "setRotationRad",
                [](Sprite& self, f32 angle) {
                    return self.setRotation(sf::radians(angle));
                },
                "setScale",
                [](Sprite& self, const Scale& scale) {
                    return self.setScale(scale);
                },
                "setOrigin",
                [](Sprite& self, const Position& origin) {
                    return self.setOrigin(origin);
                },
                "getPosition",
                [](Sprite& self) {
                    return self.getPosition();
                },
                "getRotation",
                [](Sprite& self) {
                    return self.getRotation().asDegrees();
                },
                "getRotationRad",
                [](Sprite& self) {
                    return self.getRotation().asRadians();
                },
                "getScale",
                [](Sprite& self) {
                    return self.getScale();
                },
                "getOrigin",
                [](Sprite& self) {
                    return self.getOrigin();
                },
                "move",
                [](Sprite& self, const Position& offset) {
                    return self.move(offset);
                },
                "rotate",
                [](Sprite& self, f32 angle) {
                    return self.rotate(sf::degrees(angle));
                },
                "rotateRad",
                [](Sprite& self, f32 angle) {
                    return self.rotate(sf::radians(angle));
                },
                "scale",
                [](Sprite& self, const Scale& factors) {
                    return self.scale(factors);
                },
                "getTransform",
                [](Sprite& self) {
                    return self.getTransform();
                },
                "getInverseTransform",
                [](Sprite& self) {
                    return self.getInverseTransform();
                },
                "draw",
                [](Sprite& self, Window& window) {
                    return self.draw(window);
                },
                "setTextureRect",
                [](Sprite& self, const Frame& rect) {
                    return self.setTextureRect(rect);
                },
                "getTextureRect",
                [](Sprite& self) {
                    return self.getTextureRect();
                },
                "setColor",
                [](Sprite& self, const Color& color) {
                    return self.setColor(color);
                },
                "getTexture",
                [](Sprite& self) {
                    return self.getTexture();
                },
                "getColor",
                [](Sprite& self) {
                    return self.getColor();
                },
                "getGlobalBounds",
                [](Sprite& self) {
                    return self.getGlobalBounds();
                },
                "getLocalBounds",
                [](Sprite& self) {
                    return self.getLocalBounds();
                }
            );
        }

        void load_animator_component()
        {
            m_kat.new_usertype<Animation>("Animation",
                sol::constructors<Animation()>(),
                "addFrame",
                [](Animation& self, const Frame& frame) {
                    self.addFrame(frame);
                    return self;
                },
                "addFrames",
                [](Animation& self, const std::vector<Frame>& frames) {
                    self.addFrames(frames);
                    return self;
                },
                "setLoop",
                [](Animation& self, bool loop) {
                    self.setLoop(loop);
                    return self;
                },
                "setSpeed",
                [](Animation& self, f32 speed) {
                    self.setSpeed(speed);
                    return self;
                },

                "frames", &Animation::frames,
                "speed", &Animation::speed,
                "loop", &Animation::loop
            );

            m_kat["AnimationState::Stopped"] = AnimationState::Stopped;
            m_kat["AnimationState::Playing"] = AnimationState::Playing;
            m_kat["AnimationLoop::Default"] = AnimationLoop::Default;
            m_kat["AnimationLoop::Loop"] = AnimationLoop::Loop;
            m_kat["AnimationLoop::NoLoop"] = AnimationLoop::NoLoop;

            m_kat.new_usertype<Animator>("Animator",
                sol::constructors<Animator(Sprite&)>(),
                "addAnimation",
                [](Animator& self, const std::string& name, const Animation& animation) {
                    return self.addAnimation(name, animation);
                },
                "removeAnimation",
                [](Animator& self, const AnimationName& name) {
                    return self.removeAnimation(name);
                },
                "play",
                [](Animator& self, const AnimationName& name) {
                    return self.playAnimation(name);
                },
                "stop",
                [](Animator& self) {
                    return self.stopAnimation();
                },
                "update",
                [](Animator& self, const FrameTime& dt) {
                    return self.update(dt);
                },
                "isPlaying",
                [](Animator& self) {
                    return self.isPlaying();
                },
                "isLooping",
                [](Animator& self) {
                    return self.isLooping();
                },
                "addAnimationSpritesheetPro",
                [](Animator& self, const AnimationName& name,
                    const FrameIndexList& frames, const FrameSize& frameSize,
                    const FrameTime& frameTime, const TextureSize& textureSize,
                    bool loop) {
                    return self.addAnimationSpritesheet(name, frames, frameSize,
                        frameTime, textureSize, loop);
                },
                "addAnimationSpritesheet",
                [](Animator& self, const AnimationName& name,
                    const FrameIndexList& frames, const FrameSize& frameSize,
                    const FrameTime& frameTime, bool loop) {
                    return self.addAnimationSpritesheet(name, frames, frameSize,
                        frameTime, loop);
                }
            );
        }

        void load_batch_renderer_api()
        {
            m_kat.new_usertype<BatchRenderer>(
                "BatchRenderer",
                sol::constructors<BatchRenderer()>(),
                "add",
                [](BatchRenderer& self, const shared_drawable_t& drawable, ZAxis z) {
                    return self.add(drawable, z);
                },
                "draw",
                [](BatchRenderer& self, Window& window) {
                    return self.draw(window);
                },
                "clear",
                [](BatchRenderer& self) {
                    return self.clear();
                }
            );
        }

        void load_input_manager_api()
        {
            m_kat["InputState::Idle"] = InputState::Idle;
            m_kat["InputState::Released"] = InputState::Released;
            m_kat["InputState::Pressed"] = InputState::Pressed;
            m_kat["InputState::Held"] = InputState::Held;

            m_kat["Joystick::Count"] = Joystick::Count;
            m_kat["Joystick::ButtonCount"] = Joystick::ButtonCount;
            m_kat["Joystick::AxisCount"] = Joystick::AxisCount;

            m_kat["Joystick::Axis::X"] = Joystick::Axis::X;
            m_kat["Joystick::Axis::Y"] = Joystick::Y;
            m_kat["Joystick::Axis::Z"] = Joystick::Z;
            m_kat["Joystick::Axis::R"] = Joystick::R;
            m_kat["Joystick::Axis::U"] = Joystick::U;
            m_kat["Joystick::Axis::V"] = Joystick::V;
            m_kat["Joystick::Axis::PovX"] = Joystick::PovX;
            m_kat["Joystick::Axis::PovY"] = Joystick::PovY;

            m_kat["Keyboard::K_UNKNOWN"] = Keyboard::Key::Unknown;

            for (u32 i = 0; i < Keyboard::Key::Z - Keyboard::Key::A; ++i) {
                const std::string key = "Keyboard::K_" + std::to_string('A' + i);
                m_kat[key] = static_cast<Keyboard::Key>(Keyboard::Key::A + i);
            }
            for (u32 i = 0; i < Keyboard::Key::Num9 - Keyboard::Key::Num0; ++i) {
                const std::string key = "Keyboard::K_" + std::to_string('0' + i);
                m_kat[key] = static_cast<Keyboard::Key>(Keyboard::Key::Num0 + i);
            }
            m_kat["K_ESCAPE"] = Keyboard::Key::Escape;
            m_kat["K_LCONTROL"] = Keyboard::Key::LControl;
            m_kat["K_LSHIFT"] = Keyboard::Key::LShift;
            m_kat["K_LALT"] = Keyboard::Key::LAlt;
            m_kat["K_LSYSTEM"] = Keyboard::Key::LSystem;
            m_kat["K_RCONTROL"] = Keyboard::Key::RControl;
            m_kat["K_RSHIFT"] = Keyboard::Key::RShift;
            m_kat["K_RALT"] = Keyboard::Key::RAlt;
            m_kat["K_RSYSTEM"] = Keyboard::Key::RSystem;
            m_kat["K_MENU"] = Keyboard::Key::Menu;
            m_kat["K_LBRACKET"] = Keyboard::Key::LBracket;
            m_kat["K_RBRACKET"] = Keyboard::Key::RBracket;
            m_kat["K_SEMICOLON"] = Keyboard::Key::Semicolon;
            m_kat["K_COMMA"] = Keyboard::Key::Comma;
            m_kat["K_PERIOD"] = Keyboard::Key::Period;
            m_kat["K_QUOTE"] = Keyboard::Key::Quote;
            m_kat["K_SLASH"] = Keyboard::Key::Slash;
            m_kat["K_BACKSLASH"] = Keyboard::Key::Backslash;
            m_kat["K_TILDE"] = Keyboard::Key::Tilde;
            m_kat["K_EQUAL"] = Keyboard::Key::Equal;
            m_kat["K_SPACE"] = Keyboard::Key::Space;
            m_kat["K_RETURN"] = Keyboard::Key::Enter;
            m_kat["K_ENTER"] = Keyboard::Key::Enter;
            m_kat["K_BACKSPACE"] = Keyboard::Key::Backspace;
            m_kat["K_TAB"] = Keyboard::Key::Tab;
            m_kat["K_PAGEUP"] = Keyboard::Key::PageUp;
            m_kat["K_PAGEDOWN"] = Keyboard::Key::PageDown;
            m_kat["K_END"] = Keyboard::Key::End;
            m_kat["K_HOME"] = Keyboard::Key::Home;
            m_kat["K_INSERT"] = Keyboard::Key::Insert;
            m_kat["K_DELETE"] = Keyboard::Key::Delete;
            m_kat["K_ADD"] = Keyboard::Key::Add;
            m_kat["K_SUBTRACT"] = Keyboard::Key::Subtract;
            m_kat["K_MULTIPLY"] = Keyboard::Key::Multiply;
            m_kat["K_DIVIDE"] = Keyboard::Key::Divide;
            m_kat["K_LEFT"] = Keyboard::Key::Left;
            m_kat["K_RIGHT"] = Keyboard::Key::Right;
            m_kat["K_UP"] = Keyboard::Key::Up;
            m_kat["K_DOWN"] = Keyboard::Key::Down;
            for (u32 i = 0; i < Keyboard::Key::Numpad9 - Keyboard::Key::Numpad0; ++i) {
                const std::string key = "Keyboard::K_NUMPAD" + std::to_string('0' + i);
                m_kat[key] = static_cast<Keyboard::Key>(Keyboard::Key::Numpad0 + i);
            }
            for (u32 i = 0; i < Keyboard::Key::F15 - Keyboard::Key::F1; ++i) {
                const std::string key = "Keyboard::K_F" + std::to_string('1' + i);
                m_kat[key] = static_cast<Keyboard::Key>(Keyboard::Key::F1 + i);
            }
            m_kat["Keyboard::K_PAUSE"] = Keyboard::Key::Pause;

            m_kat["Mouse::Button::Left"] = Mouse::Button::Left;
            m_kat["Mouse::Button::Right"] = Mouse::Button::Right;
            m_kat["Mouse::Button::Middle"] = Mouse::Button::Middle;
            m_kat["Mouse::Button::XButton1"] = Mouse::Button::XButton1;
            m_kat["Mouse::Button::XButton2"] = Mouse::Button::XButton2;

            m_kat["Mouse::Wheel::VerticalWheel"] = Mouse::Wheel::VerticalWheel;
            m_kat["Mouse::Wheel::HorizontalWheel"] = Mouse::Wheel::HorizontalWheel;

            m_kat.new_usertype<InputManager>("InputManager",
                "update",
                &InputManager::update,
                "nextFrame",
                &InputManager::nextFrame,
                "isJoystickConnected",
                &InputManager::isJoystickConnected,
                "getJoystickAxisPosition",
                &InputManager::getJoystickAxisPosition,
                "getJoystickButtonState",
                &InputManager::getJoystickButtonState,
                "getKeyState",
                &InputManager::getKeyState,
                "getMouseButtonState",
                &InputManager::getMouseButtonState,
                "getMousePosition",
                &InputManager::getMousePosition,
                "setMousePosition",
                [](InputManager& inputManager, const MousePosition& position) {
                    inputManager.setMousePosition(position);
                },
                "setMousePositionRelative",
                [](InputManager& inputManager, const MousePosition& position, const Window& window) {
                    return inputManager.setMousePosition(position, window.get_handle());
                }
            );
        }

    public:
        Lua()
        {
            m_state.open_libraries(
                sol::lib::base,
                sol::lib::string,
                sol::lib::table);

            m_kat = m_state.create_named_table("Kat");

            load_window_api();
            load_basic_rect_types();
            load_basic_vector_types();
            load_texture_component();
            load_sprite_component();
            load_animator_component();
            load_batch_renderer_api();
        }
    };

}