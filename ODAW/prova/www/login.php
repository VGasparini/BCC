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