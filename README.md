# ws281xspi
--------------------------------

This plugin provides an interface to connect a nymea system with
a WS281x LED strips. It uses 
[jgarff's rpi_ws281x library](https://github.com/jgarff/rpi_ws281x)
to communicate with the hardware. See the README.md file of this
library for more details on the hardware. The plugin only implements
the serial peripheral interface (SPI) connection.

## Parameters

At present, this plugin interface provides access to the following
parameters:

__Parameters:__ (can only set once when creating the thing)

Parameter | Default | Allowed Values | Description
----------|---------|----------------|-----------------------------------
SPI Pin   | 10      | 10             | The GPIO pin of the Raspberry Pi to be used for SPI output. Since only pin 10 is present on all Raspberry Pi hardware, this is the only one supported for now.
Length    | 8       | > 0            | The number of LEDs that shall be accessed

__States:__

Parameter | Default | Allowed Values | Description
----------|---------|----------------|------------------------------
Brightness| 255     | 0-255          | LED brightness
Color     | 8       | > 0            | LED color
Power     | 0       | 0/1            | On/off switch


## Building the plugin

__Requirements:__

Follow the instructions 
[here](https://nymea.io/documentation/developers/build-env) to
setup the build environment. In addition, the scons software
package is required.

__Get the source code:__

The plugin can be obtained from its Github repository 
[here](https://github.com/hermanndetz/nymea-plugin-ws281x.git):

```
git checkout https://github.com/hermanndetz/nymea-plugin-ws281x.git
```

The plugin requires the rpi_ws281x library, available at Github 
[here](https://github.com/jgarff/rpi_ws281x). This library presently
not available in form of a DEB developer package. It is therefore 
included as git submodule with this plugin. For more details, see
the discussion [here](https://github.com/nymea/nymea-plugins/pull/305).
To obatin the sources, change to the plugin root directory
and load it as follows:

```
git submodule init
git submodule update
```

__Build the plugin:__

Create a build directory and change to it. Run qmake, where 
PATH_TO_PLUGIN_ROOT should point to the directory holding the
ws281xspi.pro file.

```
qmake PATH_TO_PLUGIN_ROOT
make
sudo make install
```

Restart your nymea:core. The plugin should be listed. Finally, add a
thing and set the parameters according to your preferences.

