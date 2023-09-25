FROM ros:humble

RUN apt-get update && apt-get install -y \
    ros-$ROS_DISTRO-rmw-cyclonedds-cpp
RUN mkdir -p /ws

ENV RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
ENV CYCLONEDDS_URI='<Domain id="any"><SharedMemory><Enable>true</></></>'
WORKDIR /ws
COPY . /ws/src

RUN . /opt/ros/$ROS_DISTRO/setup.sh \
    && colcon build

RUN echo "source /ws/install/setup.bash" >> /root/.bashrc
