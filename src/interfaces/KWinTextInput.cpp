/*
    Input Actions - Input handler that executes user-defined actions
    Copyright (C) 2024-2026 Marcin Woźniak

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "KWinTextInput.h"
#include <kwin/wayland/seat.h>
#include <kwin/wayland/textinput_v1.h>
#include <kwin/wayland/textinput_v2.h>
#include <kwin/wayland/textinput_v3.h>
#include <kwin/wayland_server.h>

namespace InputActions
{

void KWinTextInput::deleteSurroundingText(uint32_t beforeLength, uint32_t afterLength)
{
    auto *seat = KWin::waylandServer()->seat();
    if (auto *v3 = seat->textInputV3(); v3 && v3->isEnabled()) {
        v3->deleteSurroundingText(beforeLength, afterLength);
        v3->done();
    } else if (auto *v2 = seat->textInputV2(); v2 && v2->isEnabled()) {
        v2->deleteSurroundingText(beforeLength, afterLength);
    } else if (auto *v1 = seat->textInputV1(); v1 && v1->isEnabled()) {
        v1->deleteSurroundingText(beforeLength, afterLength);
    }
}

std::optional<QString> KWinTextInput::surroundingText()
{
    auto *seat = KWin::waylandServer()->seat();
    if (auto *v3 = seat->textInputV3(); v3 && v3->isEnabled()) {
        return v3->surroundingText();
    } else if (auto *v2 = seat->textInputV2(); v2 && v2->isEnabled()) {
        return v2->surroundingText();
    } else if (auto *v1 = seat->textInputV1(); v1 && v1->isEnabled()) {
        return v1->surroundingText();
    }
    return {};
}

std::optional<uint32_t> KWinTextInput::surroundingTextCursorPosition()
{
    auto *seat = KWin::waylandServer()->seat();
    if (auto *v3 = seat->textInputV3(); v3 && v3->isEnabled()) {
        return std::max(0, v3->surroundingTextCursorPosition());
    } else if (auto *v2 = seat->textInputV2(); v2 && v2->isEnabled()) {
        return std::max(0, v2->surroundingTextCursorPosition());
    } else if (auto *v1 = seat->textInputV1(); v1 && v1->isEnabled()) {
        return std::max(0, v1->surroundingTextCursorPosition());
    }
    return {};
}

void KWinTextInput::writeText(const QString &text)
{
    auto *seat = KWin::waylandServer()->seat();
    if (auto *v3 = seat->textInputV3(); v3 && v3->isEnabled()) {
        v3->sendPreEditString({}, 0, 0);
        v3->commitString(text);
        v3->done();
    } else if (auto *v2 = seat->textInputV2(); v2 && v2->isEnabled()) {
        v2->commitString(text);
        v2->setPreEditCursor(0);
        v2->preEdit({}, {});
    } else if (auto *v1 = seat->textInputV1(); v1 && v1->isEnabled()) {
        v1->commitString(text);
        v1->setPreEditCursor(0);
        v1->preEdit({}, {});
    }
}

}