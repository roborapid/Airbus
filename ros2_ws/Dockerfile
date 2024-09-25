<Auf welches Basisimage wollen wir bauen?>
<Welche Rechte brauchen wir?>

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ros-$ROS_DISTRO-ament-cmake-clang-format 

<Wie muss unsere Umgebung, bzw. die Ordnerstruktur ausschauen?>

# source the workspace in the ros_entrypoint.sh (called when shell is opened in container)
RUN sed --in-place --expression \
      '$i source "${ROS_WS}/install/setup.bash"' \
      /ros_entrypoint.sh


# create non-privileged user and create ros_ws for airbus user
RUN if [ ! -d $ROS_WS/src ]; then \
    groupadd -g 1000 -r airbus && \
    useradd -u 1000 -r -s /bin/bash -g airbus -d $HOME airbus && \
    echo '%airbus ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers && \
    mkdir -p $ROS_WS/src && \
    chown -R airbus:airbus $HOME; \
    else echo "src directory already exists, skipping airbus user setup"; \
    fi

# run program later with non-privileged user
<Welchen User wählen wir jetzt?>

# copy local project into container
COPY --chown=1000:1000 . <wohin kopieren wir unser Projekt?>

RUN /bin/bash -c '. /opt/ros/$ROS_DISTRO/setup.bash && <wie lautet der Befehl zum Bauen eines ROS-Projekts?> --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release --packages-up-to <wie lautet der Package-Name?>'

CMD [ "bash" ]
