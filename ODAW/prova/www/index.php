<html>
 <head>
  <title>Controle Despesas</title>

  <meta charset="utf-8"> 

  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>

</head>

<body class="index">
<header>

    <div class="container">

    <div class="tab-content">
        <form class="form-horizontal" action="" method="POST">
        <fieldset>
        <div class="card">
            <div class="card-header">
                <h3 class="well">Login - Gerenciador de Despesas</h3>
            </div>
        </div>
        <div class="intro-text d-flex justify-content-center" style="margin-left: 40%;" >
            <form id="contactForm" method="POST" >
                <div>
                        <div>
                            <div class="form-group" >
                                <input type="text" class="form-control" style="width: 30%;" placeholder="Usuario" id="usuario" name="usuario" value=""/>
                                <p class="help-block text-danger"></p>
                            </div>
                            <div class="form-group">
                                <input type="password" class="form-control" style="width: 30%;" placeholder="Senha" id="senha" name="senha" value=""/>
                                <p class="help-block text-danger"></p>
                            </div>
                        </div>
                    </div>
                
                <button type="submit" id="login" name="login" class="page-scroll btn btn-xl" style="margin-left:10%">Login</button>
                
            </form>
            
        </div>
        <?php
                $erro = isset($_GET['erro']) ? $_GET['erro'] : null;
                if ($erro != null) {
                    echo '<div class="alert alert-danger" style="margin-top:15px;"> Login inválido</div>';
                }
                ?>
        </div>
        </div>
    </div>
</header>

<?php

if(isset($_POST["login"])){

    $conn = mysqli_connect('db', 'user', 'test', 'avaliacaoODAW');

    $usuario = $_POST['usuario'];
    $senha = $_POST['senha'];

    $query = "SELECT * FROM usuario WHERE login ='$usuario' AND senha = '$senha' ";
    $resultado = mysqli_query($conn,$query);
    $linha = mysqli_fetch_assoc($resultado);

    if (!empty($linha)) {
        session_start();
        $_SESSION['loggedin'] = true;
        $_SESSION['username'] = $username;
        
        echo '<script type="text/javascript">
           window.location = "./home.php"
      </script>';
    } else {
        echo '<script type="text/javascript">
           window.location = "./index.php?erro=login"
      </script>';
    }
}
?>

</body>
</html>
