<html>
 <head>
  <title>BRUTE</title>

  <meta charset="utf-8"> 

  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>

</head>
<?php

$ies_mapping = array(
    0 => "UDESC",
    1 => "UNIVILLE",
    2 => "UNISOCIESC",
    3 => "PUC",
    4 => "Outra"
);


$id = 0;

if(!empty($_GET['id']))
{
    $id = $_REQUEST['id'];
}

if(!empty($_POST))
{
    $id = $_POST['id'];

    $conn = mysqli_connect('db', 'user', 'test', "myDb");
    $sql = "DELETE FROM Competidor where id = '".$id."'";
    $query = mysqli_query($conn, $sql);
    if($query = mysqli_query($conn, $sql)){
        echo  "<script>alert('Competidor excluido com sucesso!');</script>";
    }else{
        echo  "<script>alert('Falha ao excluir competidor no banco!');</script>";
    }
    mysqli_close($conn);
}
?>

<body>
    <div class="container">
    <div class="tab-content">
        <div class="card">
            <div class="card-header">
                <h3 class="well"> Excluir Competidor </h3>
            </div>
            <div class="card-body">
            <?php
                $conn = mysqli_connect('db', 'user', 'test', "myDb");
                
                $list_query = "SELECT * From Competidor WHERE id ='".$id."'";
                $result = mysqli_query($conn, $list_query);
                $value = $result->fetch_array(MYSQLI_ASSOC);

                echo '<table class="table table-striped">';
                echo '<thead><tr><th>Nome</th><th>Idade</th><th>Time</th><th>Email</th><th>Instituição</th><th>CPF</th></tr></thead>';
                echo '<tr>';
                echo '<td>' . $value['name'] . '</td>';
                echo '<td>' . $value['idade'] . '</td>';
                echo '<td>' . $value['team'] . '</td>';
                echo '<td>' . $value['email'] . '</td>';
                echo '<td>' . $ies_mapping[$value['ie']] . '</td>';
                if ($value['ie'] == 0)
                    echo '<td>' . $value['cpf'] . '</td>';
                else
                    echo '<td> -- </td>';
                echo '</tr>';
                echo '</table>';
                ?>
                <form class="form-horizontal" action="delete.php" method="post">
                    <input type="hidden" name="id" value="<?php echo $id;?>" />
                    <?php if (!$value): ?>
                        <div class="alert alert-danger"> ID de Competidor inválido</div>
                            <a href="index.php" type="btn" class="btn btn-default">Voltar</a>
                    <?php endif; ?>
                    <?php if ($value): ?>
                        <div class="alert alert-danger"> Deseja excluir o competidor?
                        <div class="form actions">
                        <button type="submit" class="btn btn-danger">Sim</button>
                            <a href="index.php" type="btn" class="btn btn-default">Não</a>
                        </div>
                        </div>
                    <?php endif; ?>
                    </div>
                    
                </form>
            </div>
        </div>
    </body>

    </html>