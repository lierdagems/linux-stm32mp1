# 初始化st编译链

```
source /opt/st/stm32mp1-demo-logicanalyser/2.6-snapshot/environment-setup-cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi

```

# 在源码中编译


```
make ARCH=arm stm32mp1_defconfig
make ARCH=arm menuconfig
make CROSS_COMPILE=arm-ostl-linux-musl- ARCH=arm uImage vmlinux dtbs LOADADDR=0xC2000040
make CROSS_COMPILE=arm-ostl-linux-musl- ARCH=arm modules

make CROSS_COMPILE=arm-ostl-linux-musl- ARCH=arm INSTALL_MOD_PATH="$PWD/install_artifact" modules_install
mkdir -p $PWD/install_artifact/boot/
cp $PWD/arch/arm/boot/uImage $PWD/install_artifact/boot/
cp $PWD/arch/arm/boot/dts/st*.dtb $PWD/install_artifact/boot/


```

# 指定编译目录


```
make ARCH=arm stm32mp1_defconfig O="$PWD/../build"
make ARCH=arm menuconfig O="$PWD/../build"
make CROSS_COMPILE=arm-linux-gnueabi- ARCH=arm uImage vmlinux dtbs LOADADDR=0xC2000040 O="$PWD/../build"
make CROSS_COMPILE=arm-linux-gnueabi- ARCH=arm modules O="$PWD/../build"

make CROSS_COMPILE=arm-linux-gnueabi- ARCH=arm INSTALL_MOD_PATH="$PWD/../build/install_artifact" modules_install O="$PWD/../build"
mkdir -p $PWD/../build/install_artifact/boot/
cp $PWD/../build/arch/arm/boot/uImage $PWD/../build/install_artifact/boot/
cp $PWD/../build/arch/arm/boot/dts/st*.dtb $PWD/../build/install_artifact/boot/

```

默认设备树文件名：stm32mp157c-dk2.dtb

# 烧写镜像

```
//格式化
dd if=/dev/zero of=/dev/sdc bs=10M count=1
//烧写镜像
dd if=system.img of=/dev/sdc bs=1M && sync
或
dd if=system.img of=/dev/sdc bs=1M conv=fdatasync

```

