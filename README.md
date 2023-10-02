
# Overview

This repository demonstrates possible memory leak in using CycloneDDS with Iceoryx.

# Steps to reproduce

Build docker image:

```
docker build -f Dockerfile -t cyclone-leak-test .
```

Open four terminal windows.
In the first terminal window run:

```
docker run -it --shm-size 1GB --rm --name cyclone-leak-test cyclone-leak-test iox-roudi
```

In the second terminal window run:

```
docker exec -it cyclone-leak-test bash -c ". /ws/install/setup.bash && ros2 run test_listener test_listener"
```

In the third terminal window run:

```
docker exec -it cyclone-leak-test bash -c ". /ws/install/setup.bash && while true; do ros2 run test_publisher test_publisher; done"
```

In the fourth terminal window again run:

```
docker exec -it cyclone-leak-test bash -c ". /ws/install/setup.bash && while true; do ros2 run test_publisher test_publisher; done"
```

And wait a minute.

After some time you will most likely start to get errors:
```
1696239369.966511 [0] test_liste: DDS reader with topic rt/topic : iceoryx subscriber - TOO_MANY_CHUNKS_HELD_IN_PARALLEL -could not take sample
```

# Explanation

The issue was observed in ROS system with a few dozens of nodes. Using the iox-introspection-client we observed that when some nodes are restared the number of allocated memory chunks increases.

This repository shows a minimal case so subscriber's history depth is set to quickly trigger a warning.

