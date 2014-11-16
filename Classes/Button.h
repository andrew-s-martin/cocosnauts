//
//  Button.h
//  ChessExplorer
//
//  Created by Jamie Yung on 13/11/2014.
//
//

#ifndef __ChessExplorer__Button__
#define __ChessExplorer__Button__

#include "2d/CCLabel.h"
#include "ui/UIWidget.h"

USING_NS_CC;

namespace NSC {
    namespace ui {
        class Button : public cocos2d::ui::Widget {
        public:
            
            /**
             * Default constructor
             */
            Button();
            
            /**
             * Default destructor
             */
            virtual ~Button();
            
            /**
             * Allocates and initializes.
             */
            static Button* create();
            
            /**
             * create a button with custom textures
             * @normalImage normal state texture name
             * @selectedImage  selected state texture name
             * @disableImage disabled state texture name
             * @param texType    @see UI_TEX_TYPE_LOCAL
             */
            static Button* create(const std::string& normalImage,
                                  const std::string& selectedImage = "",
                                  const std::string& disableImage = "",
                                  TextureResType texType = TextureResType::LOCAL);
            
            /**
             * Load textures for button.
             *
             * @param normal    normal state texture name.
             *
             * @param selected    selected state texture name.
             *
             * @param disabled    disabled state texture name.
             *
             * @param texType    @see TextureResType
             */
            void loadTextures(const std::string& normal,
                              const std::string& selected,
                              const std::string& disabled = "",
                              TextureResType texType = TextureResType::LOCAL);
            
            /**
             * Load normal state texture for button.
             *
             * @param normal    normal state texture.
             *
             * @param texType    @see TextureResType
             */
            void loadTextureNormal(const std::string& normal, TextureResType texType = TextureResType::LOCAL);
            
            /**
             * Load selected state texture for button.
             *
             * @param selected    selected state texture.
             *
             * @param texType    @see TextureResType
             */
            void loadTexturePressed(const std::string& selected, TextureResType texType = TextureResType::LOCAL);
            
            /**
             * Load dark state texture for button.
             *
             * @param disabled    dark state texture.
             *
             * @param texType    @see TextureResType
             */
            void loadTextureDisabled(const std::string& disabled, TextureResType texType = TextureResType::LOCAL);
            
            /**
             * Sets capinsets for button, if button is using scale9 renderer.
             *
             * @param capInsets    capinsets for button
             */
            void setCapInsets(const Rect &capInsets);
            
            /**
             * Sets capinsets for button, if button is using scale9 renderer.
             *
             * @param capInsets    capinsets for button
             */
            void setCapInsetsNormalRenderer(const Rect &capInsets);
            
            const Rect& getCapInsetsNormalRenderer()const;
            
            /**
             * Sets capinsets for button, if button is using scale9 renderer.
             *
             * @param capInsets    capinsets for button
             */
            void setCapInsetsPressedRenderer(const Rect &capInsets);
            
            const Rect& getCapInsetsPressedRenderer()const;
            
            /**
             * Sets capinsets for button, if button is using scale9 renderer.
             *
             * @param capInsets    capinsets for button
             */
            void setCapInsetsDisabledRenderer(const Rect &capInsets);
            
            const Rect& getCapInsetsDisabledRenderer()const;
            
            /**
             * Sets if button is using scale9 renderer.
             *
             * @param true that using scale9 renderer, false otherwise.
             */
            virtual void setScale9Enabled(bool able);
            
            bool isScale9Enabled()const;
            
            /**
             * Changes if button can be clicked zoom effect.
             *
             * @param true that can be clicked zoom effect, false otherwise.
             */
            void setPressedActionEnabled(bool enabled);
            
            //override "ignoreContentAdaptWithSize" method of widget.
            virtual void ignoreContentAdaptWithSize(bool ignore) override;
            
            //override "getVirtualRendererSize" method of widget.
            virtual const Size& getVirtualRendererSize() const override;
            
            //override "getVirtualRenderer" method of widget.
            virtual Node* getVirtualRenderer() override;
            
            /**
             * Returns the "class name" of widget.
             */
            virtual std::string getDescription() const override;
            
            void setTitleText(const std::string& text);
            const std::string& getTitleText() const;
            void setTitleColor(const Color3B& color);
            const Color3B& getTitleColor() const;
            void setTitleFontSize(float size);
            float getTitleFontSize() const;
            void setTitleFontName(const std::string& fontName);
            const std::string& getTitleFontName() const;
            
            void setPressedColor(const cocos2d::Color3B& color);
            
        CC_CONSTRUCTOR_ACCESS:
            virtual bool init() override;
            virtual bool init(const std::string& normalImage,
                              const std::string& selectedImage = "",
                              const std::string& disableImage = "",
                              TextureResType texType = TextureResType::LOCAL);
            
            
        protected:
            virtual void initRenderer() override;
            virtual void onPressStateChangedToNormal() override;
            virtual void onPressStateChangedToPressed() override;
            virtual void onPressStateChangedToDisabled() override;
            virtual void onSizeChanged() override;
            
            virtual void updateFlippedX() override;
            virtual void updateFlippedY() override;
            
            void updateTexturesRGBA();
            
            void normalTextureScaleChangedWithSize();
            void pressedTextureScaleChangedWithSize();
            void disabledTextureScaleChangedWithSize();
            
            virtual void adaptRenderers() override;
            void updateTitleLocation();
            
            virtual Widget* createCloneInstance() override;
            virtual void copySpecialProperties(Widget* model) override;
            
        protected:
            Node* _buttonNormalRenderer;
            Node* _buttonClickedRenderer;
            Node* _buttonDisableRenderer;
            Label* _titleRenderer;
            std::string _normalFileName;
            std::string _clickedFileName;
            std::string _disabledFileName;
            bool _prevIgnoreSize;
            bool _scale9Enabled;
            Rect _capInsetsNormal;
            Rect _capInsetsPressed;
            Rect _capInsetsDisabled;
            TextureResType _normalTexType;
            TextureResType _pressedTexType;
            TextureResType _disabledTexType;
            Size _normalTextureSize;
            Size _pressedTextureSize;
            Size _disabledTextureSize;
            bool _pressedActionEnabled;
            Color3B _titleColor;
            Color3B _pressedColor;
            float _normalTextureScaleXInSize;
            float _normalTextureScaleYInSize;
            float _pressedTextureScaleXInSize;
            float _pressedTextureScaleYInSize;
            bool _normalTextureLoaded;
            bool _pressedTextureLoaded;
            bool _disabledTextureLoaded;
            bool _normalTextureAdaptDirty;
            bool _pressedTextureAdaptDirty;
            bool _disabledTextureAdaptDirty;
            
        private:
            enum class FontType
            {
                SYSTEM,
                TTF
            };
            
            std::string _fontName;
            int _fontSize;
            FontType _type;
        };
        
    }
}

#endif /* defined(__ChessExplorer__Button__) */
