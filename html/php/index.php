<?php
$age = date_diff(date_create("1992-12-06"), date_create())->y;
?>

<!DOCTYPE html>

<html>
<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1">
		<title>Archauve</title>
		<meta property="og:type" content="website">
		<meta property="og:title" content="Archauve">
		<meta property="og:site_name" content="Archauve.chauve">
		<meta property="og:url" content="Archauve.chauve">
		<meta property="og:locale" content="en_US">
	</head>
	<body>
		<main>
			<header>
				Voici Archauve
				<div class="lead">Responsable pédagogique des chauves, il a <?= $age ?> années de maturation à son actif </div>
			</header>
			<nav>
				<a href="https://github.com/devoil-g" target="_blank"> Son GitHub</a>
				<a href="https://www.linkedin.com/in/guillaume-devoille-00478064/?originalSubdomain=fr" target="_blank"> Son LinkedIn</a>
			</nav>
		</main>
		<img src="http://image.noelshack.com/fichiers/2022/10/2/1646741180-archauve.jpg" width="400" height="500" alt="ARCHAUVE"> </img>
		 <div>Savourez-la cette image elle as demandé une logistique que vous imaginez peu. </div>
	</body>
</html>
