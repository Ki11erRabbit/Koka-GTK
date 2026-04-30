{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    koka
    gtk4
    pkg-config
    glib
  ];
}