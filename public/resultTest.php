<?php

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

 $connection = ssh2_connect('ec2-34-249-101-43.eu-west-1.compute.amazonaws.com', 22);
if (
ssh2_auth_password($connection, 'public', 'PubFi$h412')
)
{
    echo "Authentication success";
} else {
    die('Authentication failed');
}

ssh2_exec($connection, 'sh result_script.sh');
header('Location: http://ec2-34-249-101-43.eu-west-1.compute.amazonaws.com/');
?>