//
//  Button.cpp
//  ChessExplorer
//
//  Created by Jamie Yung on 13/11/2014.
//
//

#include "Button.h"
#include "FontManager.h"
#include "LayoutHelper.h"
#include "extensions/GUI/CCControlExtension/CCScale9Sprite.h"

using namespace NSC::ui;

static const int NORMAL_RENDERER_Z = (-2);
static const int PRESSED_RENDERER_Z = (-2);
static const int DISABLED_RENDERER_Z = (-2);
static const int TITLE_RENDERER_Z = (-1);

Button::Button():
_buttonNormalRenderer(nullptr),
_buttonClickedRenderer(nullptr),
_buttonDisableRenderer(nullptr),
_titleRenderer(nullptr),
_normalFileName(""),
_clickedFileName(""),
_disabledFileName(""),
_prevIgnoreSize(true),
_scale9Enabled(false),
_capInsetsNormal(Rect::ZERO),
_capInsetsPressed(Rect::ZERO),
_capInsetsDisabled(Rect::ZERO),
_normalTexType(TextureResType::LOCAL),
_pressedTexType(TextureResType::LOCAL),
_disabledTexType(TextureResType::LOCAL),
_normalTextureSize(_contentSize),
_pressedTextureSize(_contentSize),
_disabledTextureSize(_contentSize),
_pressedActionEnabled(false),
_titleColor(cocos2d::Color3B::BLACK),
_pressedColor(cocos2d::Color3B::RED),
_normalTextureScaleXInSize(1.0f),
_normalTextureScaleYInSize(1.0f),
_pressedTextureScaleXInSize(1.0f),
_pressedTextureScaleYInSize(1.0f),
_normalTextureLoaded(false),
_pressedTextureLoaded(false),
_disabledTextureLoaded(false),
_normalTextureAdaptDirty(true),
_pressedTextureAdaptDirty(true),
_disabledTextureAdaptDirty(true),
_fontName("Thonburi"),
_fontSize(10),
_type(FontType::SYSTEM)
{
    setTouchEnabled(true);
}

Button::~Button()
{
}

Button* Button::create()
{
    Button* widget = new Button();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

Button* Button::create(const std::string &normalImage,
                       const std::string& selectedImage ,
                       const std::string& disableImage,
                       TextureResType texType)
{
    Button *btn = new Button;
    if (btn && btn->init(normalImage,selectedImage,disableImage,texType)) {
        btn->autorelease();
        return btn;
    }
    CC_SAFE_DELETE(btn);
    return nullptr;
}

bool Button::init(const std::string &normalImage,
                  const std::string& selectedImage ,
                  const std::string& disableImage,
                  TextureResType texType)
{
    bool ret = true;
    do {
        if (!Widget::init()) {
            ret = false;
            break;
        }
        
        this->loadTextures(normalImage, selectedImage, disableImage,texType);
    } while (0);
    return ret;
}

bool Button::init()
{
    if (Widget::init())
    {
        return true;
    }
    return false;
}

void Button::initRenderer()
{
    _buttonNormalRenderer = Sprite::create();
    _buttonClickedRenderer = Sprite::create();
    _buttonDisableRenderer = Sprite::create();
    _titleRenderer = cocos2d::Label::createWithTTF("",
                                                   NSC::FontManager::getFontName(NSC::FontManager::ITALIC),
                                                   LayoutHelper::getNormalFontSize());
    _titleRenderer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _titleRenderer->setColor(_titleColor);
    
    addProtectedChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    addProtectedChild(_buttonClickedRenderer, PRESSED_RENDERER_Z, -1);
    addProtectedChild(_buttonDisableRenderer, DISABLED_RENDERER_Z, -1);
    addProtectedChild(_titleRenderer, TITLE_RENDERER_Z, -1);
}

void Button::setScale9Enabled(bool able)
{
    if (_scale9Enabled == able)
    {
        return;
    }
    _brightStyle = BrightStyle::NONE;
    _scale9Enabled = able;
    removeProtectedChild(_buttonNormalRenderer);
    removeProtectedChild(_buttonClickedRenderer);
    removeProtectedChild(_buttonDisableRenderer);
    _buttonNormalRenderer = nullptr;
    _buttonClickedRenderer = nullptr;
    _buttonDisableRenderer = nullptr;
    if (_scale9Enabled)
    {
        _buttonNormalRenderer = extension::Scale9Sprite::create();
        _buttonClickedRenderer = extension::Scale9Sprite::create();
        _buttonDisableRenderer = extension::Scale9Sprite::create();
    }
    else
    {
        _buttonNormalRenderer = Sprite::create();
        _buttonClickedRenderer = Sprite::create();
        _buttonDisableRenderer = Sprite::create();
    }
    
    loadTextureNormal(_normalFileName, _normalTexType);
    loadTexturePressed(_clickedFileName, _pressedTexType);
    loadTextureDisabled(_disabledFileName, _disabledTexType);
    addProtectedChild(_buttonNormalRenderer, NORMAL_RENDERER_Z, -1);
    addProtectedChild(_buttonClickedRenderer, PRESSED_RENDERER_Z, -1);
    addProtectedChild(_buttonDisableRenderer, DISABLED_RENDERER_Z, -1);
    if (_scale9Enabled)
    {
        bool ignoreBefore = _ignoreSize;
        ignoreContentAdaptWithSize(false);
        _prevIgnoreSize = ignoreBefore;
    }
    else
    {
        ignoreContentAdaptWithSize(_prevIgnoreSize);
    }
    setCapInsetsNormalRenderer(_capInsetsNormal);
    setCapInsetsPressedRenderer(_capInsetsPressed);
    setCapInsetsDisabledRenderer(_capInsetsDisabled);
    setBright(_bright);
}

bool Button::isScale9Enabled()const
{
    return _scale9Enabled;
}

void Button::ignoreContentAdaptWithSize(bool ignore)
{
    if (!_scale9Enabled || (_scale9Enabled && !ignore))
    {
        Widget::ignoreContentAdaptWithSize(ignore);
        _prevIgnoreSize = ignore;
    }
}

void Button::loadTextures(const std::string& normal,
                          const std::string& selected,
                          const std::string& disabled,
                          TextureResType texType)
{
    loadTextureNormal(normal,texType);
    loadTexturePressed(selected,texType);
    loadTextureDisabled(disabled,texType);
}

void Button::loadTextureNormal(const std::string& normal,TextureResType texType)
{
    if (normal.empty())
    {
        return;
    }
    _normalFileName = normal;
    _normalTexType = texType;
    if (_scale9Enabled)
    {
        extension::Scale9Sprite* normalRendererScale9 = static_cast<extension::Scale9Sprite*>(_buttonNormalRenderer);
        switch (_normalTexType)
        {
            case TextureResType::LOCAL:
                normalRendererScale9->initWithFile(normal);
                break;
            case TextureResType::PLIST:
                normalRendererScale9->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        normalRendererScale9->setCapInsets(_capInsetsNormal);
    }
    else
    {
        Sprite* normalRenderer = static_cast<Sprite*>(_buttonNormalRenderer);
        switch (_normalTexType)
        {
            case TextureResType::LOCAL:
                normalRenderer->setTexture(normal);
                break;
            case TextureResType::PLIST:
                normalRenderer->setSpriteFrame(normal);
                break;
            default:
                break;
        }
    }
    _normalTextureSize = _buttonNormalRenderer->getContentSize();
    updateFlippedX();
    updateFlippedY();
    
    updateContentSizeWithTextureSize(_normalTextureSize);
    _normalTextureLoaded = true;
    _normalTextureAdaptDirty = true;
}

void Button::loadTexturePressed(const std::string& selected,TextureResType texType)
{
    if (selected.empty())
    {
        return;
    }
    _clickedFileName = selected;
    _pressedTexType = texType;
    if (_scale9Enabled)
    {
        extension::Scale9Sprite* clickedRendererScale9 = static_cast<extension::Scale9Sprite*>(_buttonClickedRenderer);
        switch (_pressedTexType)
        {
            case TextureResType::LOCAL:
                clickedRendererScale9->initWithFile(selected);
                break;
            case TextureResType::PLIST:
                clickedRendererScale9->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        clickedRendererScale9->setCapInsets(_capInsetsPressed);
    }
    else
    {
        Sprite* clickedRenderer = static_cast<Sprite*>(_buttonClickedRenderer);
        switch (_pressedTexType)
        {
            case TextureResType::LOCAL:
                clickedRenderer->setTexture(selected);
                break;
            case TextureResType::PLIST:
                clickedRenderer->setSpriteFrame(selected);
                break;
            default:
                break;
        }
    }
    _pressedTextureSize = _buttonClickedRenderer->getContentSize();
    updateFlippedX();
    updateFlippedY();
    
    _pressedTextureLoaded = true;
    _pressedTextureAdaptDirty = true;
}

void Button::loadTextureDisabled(const std::string& disabled,TextureResType texType)
{
    if (disabled.empty())
    {
        return;
    }
    _disabledFileName = disabled;
    _disabledTexType = texType;
    if (_scale9Enabled)
    {
        extension::Scale9Sprite* disabledScale9 = static_cast<extension::Scale9Sprite*>(_buttonDisableRenderer);
        switch (_disabledTexType)
        {
            case TextureResType::LOCAL:
                disabledScale9->initWithFile(disabled);
                break;
            case TextureResType::PLIST:
                disabledScale9->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        disabledScale9->setCapInsets(_capInsetsDisabled);
    }
    else
    {
        Sprite* disabledRenderer = static_cast<Sprite*>(_buttonDisableRenderer);
        switch (_disabledTexType)
        {
            case TextureResType::LOCAL:
                disabledRenderer->setTexture(disabled);
                break;
            case TextureResType::PLIST:
                disabledRenderer->setSpriteFrame(disabled);
                break;
            default:
                break;
        }
    }
    _disabledTextureSize = _buttonDisableRenderer->getContentSize();
    updateFlippedX();
    updateFlippedY();
    
    _disabledTextureLoaded = true;
    _disabledTextureAdaptDirty = true;
}

void Button::setCapInsets(const Rect &capInsets)
{
    setCapInsetsNormalRenderer(capInsets);
    setCapInsetsPressedRenderer(capInsets);
    setCapInsetsDisabledRenderer(capInsets);
}

void Button::setCapInsetsNormalRenderer(const Rect &capInsets)
{
    _capInsetsNormal = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_buttonNormalRenderer)->setCapInsets(capInsets);
}

const Rect& Button::getCapInsetsNormalRenderer()const
{
    return _capInsetsNormal;
}

void Button::setCapInsetsPressedRenderer(const Rect &capInsets)
{
    _capInsetsPressed = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_buttonClickedRenderer)->setCapInsets(capInsets);
}

const Rect& Button::getCapInsetsPressedRenderer()const
{
    return _capInsetsPressed;
}

void Button::setCapInsetsDisabledRenderer(const Rect &capInsets)
{
    _capInsetsDisabled = capInsets;
    if (!_scale9Enabled)
    {
        return;
    }
    static_cast<extension::Scale9Sprite*>(_buttonDisableRenderer)->setCapInsets(capInsets);
}

const Rect& Button::getCapInsetsDisabledRenderer()const
{
    return _capInsetsDisabled;
}

void Button::onPressStateChangedToNormal()
{
    _buttonNormalRenderer->setVisible(true);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(false);
    if (_pressedTextureLoaded)
    {
        if (_pressedActionEnabled)
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonClickedRenderer->stopAllActions();
            cocos2d::Action *zoomAction =
            cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.5f,
                                                                     _pressedTextureScaleXInSize,
                                                                     _pressedTextureScaleYInSize));
            _buttonNormalRenderer->runAction(zoomAction);
            
            cocos2d::Action *zoomActionTitle =
            cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.5f,
                                                                     1,
                                                                     1));
            _titleRenderer->runAction(zoomActionTitle);
            
            _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            updateTexturesRGBA();
        }
        else
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
        }
    }
}

void Button::updateTexturesRGBA()
{
    _buttonNormalRenderer->setColor(this->getColor());
    _buttonClickedRenderer->setColor(this->getColor());
    _buttonDisableRenderer->setColor(this->getColor());
    
    _buttonNormalRenderer->setOpacity(this->getOpacity());
    _buttonClickedRenderer->setOpacity(this->getOpacity());
    _buttonDisableRenderer->setOpacity(this->getOpacity());
}

void Button::onPressStateChangedToPressed()
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("bloop.mp3");
    
    if (_pressedTextureLoaded)
    {
        _buttonNormalRenderer->setVisible(false);
        _buttonClickedRenderer->setVisible(true);
        _buttonDisableRenderer->setVisible(false);
        if (_pressedActionEnabled)
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonClickedRenderer->stopAllActions();
            cocos2d::Action *zoomAction =
            cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.5f,
                                                                     _pressedTextureScaleXInSize*0.9f,
                                                                     _pressedTextureScaleYInSize*0.9f));
            _buttonClickedRenderer->runAction(zoomAction);
            
            cocos2d::Action *zoomActionTitle =
            cocos2d::EaseElasticOut::create(cocos2d::ScaleTo::create(0.5f,
                                                                     0.9f,
                                                                     0.9f));
            _titleRenderer->runAction(zoomActionTitle);
            
            _buttonNormalRenderer->setScale(_normalTextureScaleXInSize*0.9f, _normalTextureScaleYInSize*0.9f);
        }
    }
    else
    {
        _buttonNormalRenderer->setVisible(true);
        _buttonClickedRenderer->setVisible(true);
        _buttonDisableRenderer->setVisible(false);
        if (_scale9Enabled)
        {
            _buttonNormalRenderer->setColor(cocos2d::Color3B::GRAY);
        }
        else
        {
            _buttonNormalRenderer->stopAllActions();
            _buttonNormalRenderer->setScale(_normalTextureScaleXInSize*0.9f, _normalTextureScaleYInSize*0.9f);
        }
    }
}

void Button::onPressStateChangedToDisabled()
{
    _buttonNormalRenderer->setVisible(false);
    _buttonClickedRenderer->setVisible(false);
    _buttonDisableRenderer->setVisible(true);
    _buttonNormalRenderer->setScale(_normalTextureScaleXInSize, _normalTextureScaleYInSize);
    _buttonClickedRenderer->setScale(_pressedTextureScaleXInSize, _pressedTextureScaleYInSize);
}

void Button::updateFlippedX()
{
    float flip = _flippedX ? -1.0f : 1.0f;
    _titleRenderer->setScaleX(flip);
    if (_scale9Enabled)
    {
        _buttonNormalRenderer->setScaleX(flip);
        _buttonClickedRenderer->setScaleX(flip);
        _buttonDisableRenderer->setScaleX(flip);
    }
    else
    {
        static_cast<Sprite*>(_buttonNormalRenderer)->setFlippedX(_flippedX);
        static_cast<Sprite*>(_buttonClickedRenderer)->setFlippedX(_flippedX);
        static_cast<Sprite*>(_buttonDisableRenderer)->setFlippedX(_flippedX);
    }
}

void Button::updateFlippedY()
{
    float flip = _flippedY ? -1.0f : 1.0f;
    _titleRenderer->setScaleY(flip);
    if (_scale9Enabled)
    {
        _buttonNormalRenderer->setScaleY(flip);
        _buttonClickedRenderer->setScaleY(flip);
        _buttonDisableRenderer->setScaleY(flip);
    }
    else
    {
        static_cast<Sprite*>(_buttonNormalRenderer)->setFlippedY(_flippedY);
        static_cast<Sprite*>(_buttonClickedRenderer)->setFlippedY(_flippedY);
        static_cast<Sprite*>(_buttonDisableRenderer)->setFlippedY(_flippedY);
    }
}

void Button::updateTitleLocation()
{
    _titleRenderer->setPosition(Vec2(_contentSize.width * 0.5f, _contentSize.height * 0.5f));
}

void Button::onSizeChanged()
{
    Widget::onSizeChanged();
    updateTitleLocation();
    _normalTextureAdaptDirty = true;
    _pressedTextureAdaptDirty = true;
    _disabledTextureAdaptDirty = true;
}

void Button::adaptRenderers()
{
    if (_normalTextureAdaptDirty)
    {
        normalTextureScaleChangedWithSize();
        _normalTextureAdaptDirty = false;
    }
    if (_pressedTextureAdaptDirty)
    {
        pressedTextureScaleChangedWithSize();
        _pressedTextureAdaptDirty = false;
    }
    if (_disabledTextureAdaptDirty)
    {
        disabledTextureScaleChangedWithSize();
        _disabledTextureAdaptDirty = false;
    }
}

const Size& Button::getVirtualRendererSize() const
{
    return _normalTextureSize;
}

Node* Button::getVirtualRenderer()
{
    if (_bright)
    {
        switch (_brightStyle)
        {
            case BrightStyle::NORMAL:
                return _buttonNormalRenderer;
            case BrightStyle::HIGHLIGHT:
                return _buttonClickedRenderer;
            default:
                return nullptr;
        }
    }
    else
    {
        return _buttonDisableRenderer;
    }
}

void Button::normalTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _buttonNormalRenderer->setScale(1.0f);
            _normalTextureScaleXInSize = _normalTextureScaleYInSize = 1.0f;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(_buttonNormalRenderer)->setPreferredSize(_contentSize);
            _normalTextureScaleXInSize = _normalTextureScaleYInSize = 1.0f;
        }
        else
        {
            Size textureSize = _normalTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonNormalRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / textureSize.width;
            float scaleY = _contentSize.height / textureSize.height;
            _buttonNormalRenderer->setScaleX(scaleX);
            _buttonNormalRenderer->setScaleY(scaleY);
            _normalTextureScaleXInSize = scaleX;
            _normalTextureScaleYInSize = scaleY;
        }
    }
    _buttonNormalRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::pressedTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _buttonClickedRenderer->setScale(1.0f);
            _pressedTextureScaleXInSize = _pressedTextureScaleYInSize = 1.0f;
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(_buttonClickedRenderer)->setPreferredSize(_contentSize);
            _pressedTextureScaleXInSize = _pressedTextureScaleYInSize = 1.0f;
        }
        else
        {
            Size textureSize = _pressedTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonClickedRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / _pressedTextureSize.width;
            float scaleY = _contentSize.height / _pressedTextureSize.height;
            _buttonClickedRenderer->setScaleX(scaleX);
            _buttonClickedRenderer->setScaleY(scaleY);
            _pressedTextureScaleXInSize = scaleX;
            _pressedTextureScaleYInSize = scaleY;
        }
    }
    _buttonClickedRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::disabledTextureScaleChangedWithSize()
{
    if (_ignoreSize)
    {
        if (!_scale9Enabled)
        {
            _buttonDisableRenderer->setScale(1.0f);
        }
    }
    else
    {
        if (_scale9Enabled)
        {
            static_cast<extension::Scale9Sprite*>(_buttonDisableRenderer)->setPreferredSize(_contentSize);
        }
        else
        {
            Size textureSize = _disabledTextureSize;
            if (textureSize.width <= 0.0f || textureSize.height <= 0.0f)
            {
                _buttonDisableRenderer->setScale(1.0f);
                return;
            }
            float scaleX = _contentSize.width / _disabledTextureSize.width;
            float scaleY = _contentSize.height / _disabledTextureSize.height;
            _buttonDisableRenderer->setScaleX(scaleX);
            _buttonDisableRenderer->setScaleY(scaleY);
        }
    }
    _buttonDisableRenderer->setPosition(_contentSize.width / 2.0f, _contentSize.height / 2.0f);
}

void Button::setPressedActionEnabled(bool enabled)
{
    _pressedActionEnabled = enabled;
}

void Button::setTitleText(const std::string& text)
{
    _titleRenderer->setString(text);
}

const std::string& Button::getTitleText() const
{
    return _titleRenderer->getString();
}

void Button::setTitleColor(const Color3B& color)
{
    _titleRenderer->setColor(color);
}

const Color3B& Button::getTitleColor() const
{
    return _titleRenderer->getColor();
}

void Button::setTitleFontSize(float size)
{
    if (_type == FontType::SYSTEM) {
        _titleRenderer->setSystemFontSize(size);
    }
    else{
        TTFConfig config = _titleRenderer->getTTFConfig();
        config.fontSize = size;
        _titleRenderer->setTTFConfig(config);
    }
    _fontSize = size;
}

float Button::getTitleFontSize() const
{
    return _fontSize;
}

void Button::setTitleFontName(const std::string& fontName)
{
    if(FileUtils::getInstance()->isFileExist(fontName))
    {
        TTFConfig config = _titleRenderer->getTTFConfig();
        config.fontFilePath = fontName;
        config.fontSize = _fontSize;
        _titleRenderer->setTTFConfig(config);
        _type = FontType::TTF;
    } else{
        _titleRenderer->setSystemFontName(fontName);
        _type = FontType::SYSTEM;
    }
    _fontName = fontName;
}

void Button::setPressedColor(const cocos2d::Color3B &color)
{
    _pressedColor = color;
    _buttonClickedRenderer->updateDisplayedColor(_pressedColor);
}

const std::string& Button::getTitleFontName() const
{
    return _fontName;
}

std::string Button::getDescription() const
{
    return "Button";
}

cocos2d::ui::Widget* Button::createCloneInstance()
{
    return Button::create();
}

void Button::copySpecialProperties(Widget *widget)
{
    Button* button = dynamic_cast<Button*>(widget);
    if (button)
    {
        _prevIgnoreSize = button->_prevIgnoreSize;
        setScale9Enabled(button->_scale9Enabled);
        loadTextureNormal(button->_normalFileName, button->_normalTexType);
        loadTexturePressed(button->_clickedFileName, button->_pressedTexType);
        loadTextureDisabled(button->_disabledFileName, button->_disabledTexType);
        setCapInsetsNormalRenderer(button->_capInsetsNormal);
        setCapInsetsPressedRenderer(button->_capInsetsPressed);
        setCapInsetsDisabledRenderer(button->_capInsetsDisabled);
        setTitleText(button->getTitleText());
        setTitleFontName(button->getTitleFontName());
        setTitleFontSize(button->getTitleFontSize());
        setTitleColor(button->getTitleColor());
        setPressedActionEnabled(button->_pressedActionEnabled);
    }
}