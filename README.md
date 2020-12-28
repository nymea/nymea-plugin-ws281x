# ws281xspi
--------------------------------

This plugin provides an interface to connect a nymea system with
a WS281x LED strips. It uses 
[jgarff's rpi_ws281x library](https://github.com/jgarff/rpi_ws281x)
to communicate with the hardware. See the README.md file of this
library for more details on the hardware. The plugin only implements
the serial peripheral interface (SPI) connection.

## Hardware Connection

__Connect the LED strip:__

The plugin is accessing the LED strip via SPI connection. At present, only GPIO pin 10 (SPIO MOSI), which is wired to pin 19 on the GPIO header can be used. The location on the extension header of a Raspberry Pi 3B is indicated in the following table (Physical column):

<table>
<tr>
    <th>BCM</th><th>wPi</th><th>Name</th><th>Mode</th><th>V</th><th colspan=2>Physical</th><th>V</th><th>Mode</th><th>Name</th><th>wPi</th><th>BCM</th>
</tr>
<tr>
    <td></td><td></td><td>3.3v</td><td></td><td></td><td>1</td><td>2</td><td></td><td></td><td>5v</td><td></td><td></td>
</tr>
<tr>
    <td>2</td><td>8</td><td>SDA.1</td><td>ALT0</td><td>1</td><td>3</td><td>4</td><td></td><td></td><td>5v</td><td></td><td></td>
</tr>
<tr>
    <td>3</td><td>9</td><td>SCL.1</td><td>ALT0</td><td>1</td><td>5</td><td>6</td><td></td><td></td><td>0v</td><td></td><td></td>
</tr>
<tr>
    <td>4</td><td>7</td><td>GPIO. 7</td><td>IN</td><td>1</td><td>7</td><td>8</td><td>0</td><td>IN</td><td>TxD</td><td>15</td><td>14</td>
</tr>
<tr>
    <td></td><td></td><td>0v</td><td></td><td></td><td>9</td><td>10</td><td>1</td><td>IN</td><td>RxD</td><td>16</td><td>15</td>
</tr>
<tr>
    <td>17</td><td>0</td><td>GPIO. 0</td><td>IN</td><td>0</td><td>11</td><td>12</td><td>0</td><td>IN</td><td>GPIO. 1</td><td>1</td><td>18</td>
</tr>
<tr>
    <td>27</td><td>2</td><td>GPIO. 2</td><td>IN</td><td>0</td><td>13</td><td>14</td><td></td><td></td><td>0v</td><td></td><td></td>
</tr>
<tr>
    <td>22</td><td>3</td><td>GPIO. 3</td><td>IN</td><td>0</td><td>15</td><td>16</td><td>0</td><td>IN</td><td>GPIO. 4</td><td>4</td><td>23</td>
</tr>
<tr>
    <td></td><td></td><td>3.3v</td><td></td><td></td><td>17</td><td>18</td><td>0</td><td>IN</td><td>GPIO. 5</td><td>5</td><td>24</td>
</tr>
<tr>
    <td><b>10</b></td><td><b>12</b></td><td><b>MOSI</b></td><td><b>ALT0</b></td><td><b>0</b></td><td><b>19</b></td><td>20</td><td></td><td></td><td>0v</td><td></td><td></td>
</tr>
<tr>
    <td>9</td><td>13</td><td>MISO</td><td>ALT0</td><td>0</td><td>21</td><td>22</td><td>0</td><td>IN</td><td>GPIO. 6</td><td>6</td><td>25</td>
</tr>
<tr>
    <td>11</td><td>14</td><td>SCLK</td><td>ALT0</td><td>0</td><td>23</td><td>24</td><td>1</td><td>OUT</td><td>CE0</td><td>10</td><td>8</td>
</tr>
<tr>
    <td></td><td></td><td>0v</td><td></td><td></td><td>25</td><td>26</td><td>1</td><td>OUT</td><td>CE1</td><td>11</td><td>7</td>
</tr>
<tr>
    <td>0</td><td>30</td><td>SDA.0</td><td>IN</td><td>1</td><td>27</td><td>28</td><td>1</td><td>IN</td><td>SCL.0</td><td>31</td><td>1</td>
</tr>
<tr>
    <td>5</td><td>21</td><td>GPIO.21</td><td>IN</td><td>1</td><td>29</td><td>30</td><td></td><td></td><td>0v</td><td></td><td></td>
</tr>
<tr>
    <td>6</td><td>22</td><td>GPIO.22</td><td>IN</td><td>1</td><td>31</td><td>32</td><td>0</td><td>IN</td><td>GPIO.26</td><td>26</td><td>12</td>
</tr>
<tr>
    <td>13</td><td>23</td><td>GPIO.23</td><td>IN</td><td>0</td><td>33</td><td>34</td><td></td><td></td><td>0v</td><td></td><td></td>
</tr>
<tr>
    <td>19</td><td>24</td><td>GPIO.24</td><td>IN</td><td>0</td><td>35</td><td>36</td><td>0</td><td>IN</td><td>GPIO.27</td><td>27</td><td>16</td>
</tr>
<tr>
    <td>26</td><td>25</td><td>GPIO.25</td><td>IN</td><td>0</td><td>37</td><td>38</td><td>0</td><td>IN</td><td>GPIO.28</td><td>28</td><td>20</td>
</tr>
<tr>
    <td></td><td></td><td>0v</td><td></td><td></td><td>39</td><td>40</td><td>0</td><td>IN</td><td>GPIO.29</td><td>29</td><td>21</td>
</tr>
<tr>
    <th>BCM</th><th>wPi</th><th>Name</th><th>Mode</th><th>V</th><th colspan=2>Physical</th><th>V</th><th>Mode</th><th>Name</th><th>wPi</th><th>BCM</th>
</tr>
</table>

This table can be obtained from with the command `gpio readall`, which is provided by the __wiringpi__ package.

__Enable SPI:__

This plugin relies on the SPI module of the Raspberry Pi. This can be activated by running `sudo raspi-config`. From the main menu select __5 Interfacing Options__ and then __P4 SPI__. Select __Yes__ to enable the hardware and kernel modules appropriately.

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
setup the build environment.

__Get the source code:__

The plugin can be obtained from its Github repository 
[here](https://github.com/hermanndetz/nymea-plugin-ws281x.git):

```
git clone https://github.com/hermanndetz/nymea-plugin-ws281x.git
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

