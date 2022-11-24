{ pkgs }: {
	deps = [
		pkgs.htop
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}