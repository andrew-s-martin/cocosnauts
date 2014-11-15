//
//  FontManager.h
//  ChessExplorer
//
//  Created by Jamie Yung on 13/11/2014.
//
//

#ifndef __ChessExplorer__FontManager__
#define __ChessExplorer__FontManager__

#include <iostream>

namespace NSC {
    class FontManager {
    public:
        enum FontStyle {
            BOLD,
            BOLDITALIC,
            CONDLIGHT,
            CONDLIGHTITALIC,
            EXTRABOLD,
            EXTRABOLDITALIC,
            ITALIC,
            LIGHT,
            LIGHTITALIC,
            REGULAR,
            SEMIBOLD,
            SEMIBOLDITALIC
        };
        static std::string getFontName(FontStyle style);
        
    private:
        static std::string getFontStyleName(FontStyle style);
    };
}

#endif /* defined(__ChessExplorer__FontManager__) */
