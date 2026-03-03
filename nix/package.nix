{
  cmake,
  extra-cmake-modules,
  kglobalacceld,
  kwin,
  lib,
  libevdev,
  pkg-config,
  qttools,
  stdenv,
  wrapQtAppsHook,
  yaml-cpp,
  ...
}:

stdenv.mkDerivation rec {
  pname = "inputactions-kwin";
  version = "0.9.0.0";

  src = ./..;

  nativeBuildInputs = [
    cmake
    extra-cmake-modules
    wrapQtAppsHook
  ];

  buildInputs = [
    kwin
    qttools
    libevdev
    kglobalacceld
    pkg-config
    yaml-cpp
  ];

  meta = with lib; {
    description = "Linux utility for binding keyboard. mouse, touchpad and touchscreen actions to system actions (KWin compositor plugin implementation)";
    license = licenses.gpl3;
    homepage = "https://github.com/InputActions/kwin";
  };
}
