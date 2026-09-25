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

#include "KWinOverlayManager.h"
#include "pointer_input.h"
#include "window.h"
#include "workspace.h"

namespace InputActions
{

KWinOverlayManager::KWinOverlayManager()
{
    auto *workspace = KWin::workspace();
    for (auto *window : workspace->stackingOrder()) {
        onWindowAdded(window);
    }
    connect(workspace, &KWin::Workspace::windowAdded, this, &KWinOverlayManager::onWindowAdded);
    connect(workspace, &KWin::Workspace::windowRemoved, this, &KWinOverlayManager::onWindowRemoved);
}

void KWinOverlayManager::onWindowAdded(KWin::Window *window)
{
    if (window->resourceClass() != "inputactions-overlay") {
        return;
    }

    if (m_overlay) {
        disconnect(m_overlay, nullptr, this, nullptr);
    }

    connect(window, &KWin::Window::frameGeometryChanged, this, [window](const auto &) {
        auto *pointer = KWin::input()->pointer();
        auto *windowUnderPointer = KWin::workspace()->windowUnderMouse(KWin::workspace()->activeOutput());

        if (pointer->focus() != window && windowUnderPointer == window) {
            pointer->setFocus(window);
        }
    });
    m_overlay = window;
}

void KWinOverlayManager::onWindowRemoved(KWin::Window *window)
{
    if (window == m_overlay) {
        m_overlay = {};
    }
}

}