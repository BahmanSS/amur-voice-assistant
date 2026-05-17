#!/bin/bash

python3 $MIK32_UPLOADER_DIR/mik32_upload.py $1 --run-openocd \
	--openocd-exec /usr/bin/openocd \
	--openocd-target $MIK32_UPLOADER_DIR/openocd-scripts/target/mik32.cfg \
	--openocd-interface $MIK32_UPLOADER_DIR/openocd-scripts/interface/ftdi/mikron-link.cfg \
	--adapter-speed 500 --mcu-type MIK32V2
