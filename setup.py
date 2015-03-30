from distutils.core import setup, Extension

module = Extension('xu3power',
                   sources=['xu3power.c','xu3power_sensors.c'])

setup(name = "XU3Power",
      version = '1.0',
      description = 'XU3 Power measurement package.',
      ext_modules = [module])
