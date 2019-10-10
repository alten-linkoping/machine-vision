#!/bin/bash

#[[ $_ != $0 ]] && echo "" || echo "Start the script with $ source ./install.sh" exit

if [[ $_ != $0 ]]; then
    echo "Make sure that python3 and virtualenv is installed on your computer before proceeding"
    echo " >> Remember to activate the virtual enviroment when you start developing!"
    echo " >> It is done by running: source ./venv/bin/activate " 
    echo
    echo " >> And when you are done, deactivate it by running: deactivate"
    echo " >> If you are still confused please read the documentation https://virtualenv.pypa.io/en/latest/userguide/#activate-script"  
    echo 
else
    echo "Start the script with $ source ./install.sh"
    exit 1
fi

function install_env_and_packages(){
    echo "Creating a folder for virtualenv called venv..." 
    mkdir venv 
    
    echo "Creating folder for storing videos (input) and CNN models (models)"
    mkdir input
    mkdir models

    echo "Creating virtualenv..."
    virtualenv -p python3 ./venv
    chmod u+x ./venv/bin/activate 
    source ./venv/bin/activate
    echo "Installing PIP packages" 
    pip install -r requirements.txt
    deactivate 
}

while true; do
read -p "Do you wish to install the virtual enviroment? [Yn] " yn
    case $yn in
        [Yy]* ) echo Installing....; echo; install_env_and_packages; break;;
        [Nn]* ) break;;
        * ) echo "Please answer yes or no.";;
    esac
done

