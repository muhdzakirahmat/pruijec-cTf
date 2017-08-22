<html>
<?php

	include("connect.php"); 	
	
	$result=mysqli_query($conn,"SELECT * FROM `scale` WHERE `time` IN (SELECT MAX(time) FROM scale)");
?>

<head>
<title>Pet Feeder</title>

<script src="jquery.js"></script>



<link href='https://fonts.googleapis.com/css?family=Sanchez' rel='stylesheet' type='text/css'>
<link rel="stylesheet" type="text/css" href="style.css">

</head>
<body>
<center>
	<h1><b>Pet Feeder</b></h1>

<button value="180" onClick="servo1(this.value)" /><h3> Feed it </h3></button><br><br>

Weight : 
<?php 
		
		while($row = mysqli_fetch_assoc($result)) 
			{
				echo $row["value"];
			}
		
mysqli_close($conn);
?>g


<br><br><br><a href="../arduino/history.php">weight history</a>
</center>
</body>

<script>
$.ajaxSetup({timeout:1000});
function servo1(angle)
{
    TextVar = "192.168.1.107";
    ArduinoVar = "http://" + TextVar + ":80";
    $.get( ArduinoVar, { "sr1": angle })    ;
    {Connection: close};
}




</script>
</html>
