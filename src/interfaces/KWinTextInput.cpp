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

void KWinTextInput::writeText(const QString &text)
{
    auto *seat = KWin::waylandServer()->seat();
    auto *v1 = seat->textInputV1();
    auto *v2 = seat->textInputV2();
    auto *v3 = seat->textInputV3();

    if (v3->isEnabled()) {
        v3->sendPreEditString({}, 0, 0);
        v3->commitString(text);
        v3->done();
    } else if (v2->isEnabled()) {
        v2->commitString(text);
        v2->setPreEditCursor(0);
        v2->preEdit({}, {});
    } else if (v1->isEnabled()) {
        v1->commitString(text);
        v1->setPreEditCursor(0);
        v1->preEdit({}, {});
    }
}

}