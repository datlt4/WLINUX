# Add to the end of ``sudo nano ~/.bashrc``
    export PDSH_RCMD_TYPE=ssh
    export HADOOP_HOME="/home/m/hadoop"
    export PATH=$PATH:$HADOOP_HOME/bin
    export PATH=$PATH:$HADOOP_HOME/sbin
    export HADOOP_MAPRED_HOME=${HADOOP_HOME}
    export HADOOP_COMMON_HOME=${HADOOP_HOME}
    export HADOOP_HDFS_HOME=${HADOOP_HOME}
    export YARN_HOME=${HADOOP_HOME}
    export HIVE_HOME="/home/m/apache-hive"
    export PATH=$PATH:$HIVE_HOME/bin

# Install dependencies
    sudo apt-get install pdsh -y
    sudo apt install openjdk-8-jdk -y
    java -version; javac -version
    sudo apt install openssh-server openssh-client -y
    ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
    cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
    chmod 0600 ~/.ssh/authorized_keys

# Download Hadoop-3.1.2 vs Hive-3.1.2
    wget https://archive.apache.org/dist/hadoop/common/hadoop-3.1.2/hadoop-3.1.2.tar.gz
    wget https://downloads.apache.org/hive/hive-3.1.2/apache-hive-3.1.2-bin.tar.gz
    tar -xzf apache-hive-3.1.2-bin.tar.gz
    tar -xzf hadoop-3.1.2.tar.gz
    mv hadoop-3.1.2 hadoop
    mv apache-hive-3.1.2-bin apache-hive

# Run `.bashrc`  and update
    source ~/.bashrc
    sudo apt-get update

# INSTALL HADOOP

## hadoop-env.sh
    sudo nano $HADOOP_HOME/etc/hadoop/hadoop-env.sh

    export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/

## core-site.xml
    sudo nano $HADOOP_HOME/etc/hadoop/core-site.xml

    <configuration>
        <property>
            <name>fs.defaultFS</name>
            <value>hdfs://localhost:9000</value>
        </property>
        <property>
            <name>hadoop.tmp.dir</name>
            <value>/home/m/hdata</value>
        </property>
    </configuration>

## hdfs-site.xml
    sudo nano $HADOOP_HOME/etc/hadoop/hdfs-site.xml

    <configuration>
        <property>
            <name>dfs.replication</name>
            <value>1</value>
        </property>
    </configuration>

## mapred-site.xml

    sudo nano $HADOOP_HOME/etc/hadoop/mapred-site.xml

    <configuration>
        <property>
            <name>mapreduce.framework.name</name>
            <value>yarn</value>
        </property>
        <property>
            <name>yarn.app.mapreduce.am.env</name>
            <value>HADOOP_MAPRED_HOME=/home/m/hadoop</value>
        </property>
        <property>
            <name>mapreduce.map.env</name>
            <value>HADOOP_MAPRED_HOME=/home/m/hadoop</value>
        </property>
        <property>
            <name>mapreduce.reduce.env</name>
            <value>HADOOP_MAPRED_HOME=/home/m/hadoop</value>
        </property>
    </configuration>

## yarn-site.xml
    sudo nano $HADOOP_HOME/etc/hadoop/yarn-site.xml

    <configuration>
        <property>
            <name>yarn.nodemanager.aux-services</name>
            <value>mapreduce_shuffle</value>
        </property>
        <property>
            <name>yarn.nodemanager.aux-services.mapreduce.shuffle.class</name>
            <value>org.apache.hadoop.mapred.ShuffleHandler</value>
        </property> 
    </configuration>

# INSTALL HIVE
    source ~/.bashrc

## core-site.xml
    sudo nano $HADOOP_HOME/etc/hadoop/core-site.xml

    <configuration>
        <property>
            <name>hadoop.proxyuser.m.groups</name>
            <value>*</value>
        </property>
        <property>
            <name>hadoop.proxyuser.m.hosts</name>
            <value>*</value>
        </property>
        <property>
            <name>hadoop.proxyuser.server.hosts</name>
            <value>*</value>
        </property>
        <property>
            <name>hadoop.proxyuser.server.groups</name>
            <value>*</value>
        </property>
    </configuration>

# Run Hadoop
    source ~/.bashrc
    cd $HADOOP_HOME/

    $HADOOP_HOME/bin/hdfs namenode -format
    $HADOOP_HOME/sbin/start-dfs.sh
    $HADOOP_HOME/sbin/start-yarn.sh
    jps

    http://localhost:9870
    http://localhost:9864
    http://localhost:8088

    $HADOOP_HOME/bin/hadoop fs -mkdir /tmp
    $HADOOP_HOME/bin/hadoop fs -mkdir /user
    $HADOOP_HOME/bin/hadoop fs -mkdir /user/hive
    $HADOOP_HOME/bin/hadoop fs -mkdir /user/hive/warehouse
    $HADOOP_HOME/bin/hadoop fs -ls -R /

    $HADOOP_HOME/bin/hadoop fs -chmod g+w /tmp
    $HADOOP_HOME/bin/hadoop fs -chmod g+w /user/hive/warehouse

# Run Hive
    source ~/.bashrc
    cd $HIVE_HOME/
    $HIVE_HOME/bin/schematool -dbType derby -initSchema
    $HIVE_HOME/bin/hiveserver2
    $HIVE_HOME/bin/beeline -n m -u jdbc:hive2://localhost:10000

    $HIVE_HOME/bin/schematool -dbType derby -initSchema
    $HIVE_HOME/bin/hive

# Stop Hadoop

    cd $HADOOP_HOME
    sbin/stop-all.sh


# Reference:
1. [How to Install Hadoop 3 on Ubuntu – A Step-by step Installation Process](https://data-flair.training/blogs/installation-of-hadoop-3-on-ubuntu/)
2. [Apache Hive Installation – Install Hive on Ubuntu in 5 Minutes](https://data-flair.training/blogs/apache-hive-installation/)
3. [How to Install Hadoop on Ubuntu 18.04 or 20.04](https://phoenixnap.com/kb/install-hadoop-ubuntu)
4. [How to Install Apache Hive on Ubuntu](https://phoenixnap.com/kb/install-hive-on-ubuntu)
