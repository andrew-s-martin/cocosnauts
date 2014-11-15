//
//  FontManager.cpp
//  ChessExplorer
//
//  Created by Jamie Yung on 13/11/2014.
//
//

#include "FontManager.h"

std::string NSC::FontManager::getFontName(NSC::FontManager::FontStyle style) {
    std::string prefix = "OpenSans-";
    std::string styleName = getFontStyleName(style);
    std::string suffix = ".ttf";
    return prefix + styleName + suffix;
}

std::string NSC::FontManager::getFontStyleName(NSC::FontManager::FontStyle style) {
    switch (style) {
        case BOLD:
            return "Bold";
        case BOLDITALIC:
            return "BoldItalic";
        case CONDLIGHT:
            return "CondLight";
        case CONDLIGHTITALIC:
            return "CondLightItalic";
        case EXTRABOLD:
            return "ExtraBold";
        case EXTRABOLDITALIC:
            return "ExtraBoldItalic";
        case ITALIC:
            return "Italic";
        case LIGHT:
            return "Light";
        case LIGHTITALIC:
            return "LightItalic";
        case REGULAR:
            return "Regular";
        case SEMIBOLD:
            return "Semibold";
        case SEMIBOLDITALIC:
            return "SemiboldItalic";
        default:
            return "";
    }
}