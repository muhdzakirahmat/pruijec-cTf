<?php

	include("connect.php"); 	
	
	$result=mysqli_query($conn,"SELECT * FROM scale ORDER BY `time` DESC");
?>




<html lang="en">
<head>
	<meta charset="utf-8" />
	<title>Table Style</title>
	<link rel="stylesheet" type="text/css" href="table.css">
	<meta name="viewport" content="initial-scale=1.0; maximum-scale=1.0; width=device-width;">
</head>

<body>
<div class="table-title">
<h3>Feed Scale</h3>
</div>
<table class="table-fill">
<thead>
<tr>
<th class="text-left">Time</th>
<th class="text-left">Weight</th>
</tr>

      <?php 
		if (mysqli_num_rows($result) > 0) 
		{
    // output data of each row
		while($row = mysqli_fetch_assoc($result)) 
			{
			echo '<tr>';
				echo '<td>'.date('d/m/Y - H:i:s',strtotime($row["time"])).'</td>';
				echo '<td>'.$row["value"].'</td>';
			echo '</tr>';
			}
		}
 		else 
		{
			echo "0 results";
		}
		
mysqli_close($conn);
?>


</thead>
<tbody class="table-hover">
</tbody>
</table>

<a class="home">HOME</a>
  

  </body>





