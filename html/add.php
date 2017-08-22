<?php

   	include("connect.php");   	
	
	$value = $_GET['value'];

	$query = "insert into scale (value) values ('$value')"; 
   	
   	mysqli_query($conn,$query);

   	if($query)
	{
		echo "success";
	}
	else
	{
		echo"error";
	}
?>
