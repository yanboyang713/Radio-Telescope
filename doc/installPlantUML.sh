#!/bin/sh -e


sudo apt install -y graphviz default-jre

sudo mkdir -p /opt/plantuml
cd /opt/plantuml
UML=http://sourceforge.net/projects/plantuml/files/plantuml.jar/download
sudo curl -JLO ${UML}

cat <<EOF | sudo tee /usr/local/bin/plantuml
#!/bin/sh

java -jar /opt/plantuml/plantuml.jar "\$@"
EOF
sudo chmod a+x /usr/local/bin/plantuml

