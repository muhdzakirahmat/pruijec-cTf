<?php

	include("connect.php"); 	
	
	$result=mysqli_query($conn,"SELECT * FROM `scale` WHERE `time` IN (SELECT MAX(time) FROM scale)");
?>

<html>
<link href='https://fonts.googleapis.com/css?family=Sanchez' rel='stylesheet' type='text/css'>
<link rel="stylesheet" type="text/css" href="style.css">
<body>
<div class="container">
	<h1>Pet Feeder</h1>
	<div class="btn-bdg">
		<div class="btn-wrap">
			<div class="btn-body">
				<p onClick="servo1(this.value)" >Feed It</p>
			</div>
		</div>
	</div>
	<h3>Weight: 
		<?php 
		
		while($row = mysqli_fetch_assoc($result)) 
			{
				echo $row["value"];
			}
		
		mysqli_close($conn);
		?>
	g</h3>
	<a href="../arduino/history.php" class="history">Weight History</a>
</div>
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