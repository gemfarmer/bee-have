# bee-have
Open-source monitoring system for bee hives.


## Existing simililar projects

- [Solution Bee](http://solutionbee.com/?page_id=145#1446901477438-2cf97671-d6ed)
- [Arnia Hive Scales](http://www.arnia.co.uk/hive-scales/)
- [HoneyBeeNet](https://honeybeenet.gsfc.nasa.gov/)
- [SparkFun Open Source project](http://makezine.com/projects/bees-sensors-monitor-hive-health/). LEARNINGS

## What we are trying to monitor/control

- Exit/entrance rates
- Hive weight:
  - Weight over time
  - Weight of bottom hive compared to above supers
  - Weight that is bee, weight that is non-bee
- Needs to support hive health in extremely cold climates. 
- Number of bees in hive
- Temperature in different areas of the hive
- Being able to adjust/control heat
- Overall: Hive health!!
- Noticing regional trends in hive health based on surrounding land

## Equipment needed

- Scale. HoneyBeeNet recommends scales that are accurate to 0.25  or ~1134 bees
- [SparkFun Load Sensor Combinator](https://www.sparkfun.com/products/13281). Attaches to load sensors and interprets resistence in a manner that can be read by Arduinos or Particles. This can be attached to a hijacked scale.
- Alternatively, you can use a [SparkFun Open Scale](https://www.sparkfun.com/products/13261) that combines 4 load sensors with the combinator.
- Arduino/Particle
- Analytics platform
  - [analog.io](http://analog.io/#/s8Q)
  - [Phant](http://phant.io/)

## Problems

- Bees weigh ~ about 0.1 gram and hives weight many pounds. Most scales that exist aren't good at measuring both of these things
- Scales drift over time
- We would be measuring on uneven surfaces


## In motion

- [Live updates](Build.md)
