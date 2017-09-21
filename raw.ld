SECTIONS {
	code : { *(.load*); _load_size = .; *(.text*) }
	data : { *( .rodata* .rdata* .data .sdata*) }
	bss : { *(.bss*) }
	got : { *(.got*); }

	/DISCARD/ : { *(*) }
}

_got_start = ADDR(got);
_got_entry_count = SIZEOF(got) ? (SIZEOF(got) / 4) : 0;