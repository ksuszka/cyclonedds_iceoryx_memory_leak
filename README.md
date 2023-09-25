
# Overview

This repository demonstrates possible memory leak in using CycloneDDS with Iceoryx.

# Steps to reproduce

Build docker image:

```
docker build -f Dockerfile -t cyclone-leak-test .
```

Open three terminal windows.
In the first terminal window run:

```
docker run -it --shm-size 200MB --rm --name cyclone-leak-test cyclone-leak-test iox-roudi -c /ws/src/roudi_config.toml
```

In the second terminal window run:

```
docker exec -it cyclone-leak-test bash -c ". /ws/install/setup.bash && ros2 run test_listener test_listener"
```

In the third terminal window run:

```
docker exec -it cyclone-leak-test bash -c ". /ws/install/setup.bash && while true; do ros2 run test_publisher test_publisher; done"
```

And wait a minute.

After some time you will most likely start to get errors:
```
2023-09-25 10:17:51.110 [ Error ]: MemoryManager: unable to acquire a chunk with a chunk-payload size of 32The following mempools are available:  MemPool [ ChunkSize = 1064, ChunkPayloadSize = 1024, ChunkCount = 100 ]
2023-09-25 10:17:51.110 [Warning]: ICEORYX error! MEPOO__MEMPOOL_GETCHUNK_POOL_IS_RUNNING_OUT_OF_CHUNKS
Mempool [m_chunkSize = 1064, numberOfChunks = 100, used_chunks = 100 ] has no more space left
```

# Explanation

The issue was observed in ROS system with a few dozens of nodes. Using the iox-introspection-client we observed that when some nodes are restared the number of allocated memory chunks increases.

This repository shows a minimal case so Iceoryx configuration is deliberately crippled (available memory pool is very small).
Disabling the parameter event publication (setting start_parameter_event_publisher to false) makes this issue go away.
