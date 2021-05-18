<html>
 <head>
  <title>BRUTE</title>

  <meta charset="utf-8"> 

  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>

</head>
<?php


$id = null;
if (!empty($_GET['id'])) {
    $id = $_REQUEST['id'];
}

if (!empty($_POST)) {

    $form_name = $_POST['form_name'];
    $form_idade = $_POST['form_idade'];
    $form_team = $_POST['form_team'];
    $form_univ = $_POST['form_univ'];
    $form_email = $_POST['form_email'];
    $form_cpf = $_POST['form_cpf'];

    //Validação
    $validacao = true;
    if (empty($form_name)) {
        $nomeErro = 'Por favor digite o nome!';
        $validacao = false;
    }
    
    if (empty($form_idade) or $form_idade > 100) {
        $idadeErro = 'Por favor digite uma idade valida!';
        $validacao = false;
    }

    if (empty($form_team)) {
        $timeErro = 'Por favor digite um time!';
        $validacao = false;
    }

    if (empty($form_email)) {
        $emailErro = 'Por favor digite o email!';
        $validacao = false;
    } else if (!preg_match('/^\S+@\S+\.\S+$/', $form_email)) {
        $emailErro = 'Por favor digite um email válido!';
        $validacao = false;
    }

    if ($form_univ == 0 and empty($form_cpf)) {
        $cpfErro = 'Por favor digite o CPF!';
        $validacao = false;
    } else {
        if(strlen(preg_replace( '/[^0-9]/is', '', $form_cpf)) == 11){
            for ($t = 9; $t < 11; $t++) {
                for ($d = 0, $c = 0; $c < $t; $c++) {
                    $d += $form_cpf[$c] * (($t + 1) - $c);
                }
                $d = ((10 * $d) % 11) % 10;
                if ($form_cpf[$c] != $d) {
                    $cpfErro = 'Por favor digite um CPF válido!';
                    $validacao = false;
                }
            }
        } else {
            $cpfErro = 'Por favor digite um CPF válido!';
            $validacao = false;
        }
    }

    

    if(isset($_POST["submit_button"])){

        $form_name = $_POST['form_name'];
        $form_idade = $_POST['form_idade'];
        $form_team = $_POST['form_team'];
        $form_univ = $_POST['form_univ'];
        $form_email = $_POST['form_email'];
        $form_cpf = $_POST['form_cpf'];
        $sql = "UPDATE Competidor SET name = '".$form_name."',idade = '".$form_idade."',team = '".$form_team."',email = '".$form_email."',cpf = '".$form_cpf."' WHERE id = '".$id."'";
        if ($validacao) {
            $conn = mysqli_connect('db', 'user', 'test', "myDb");
            if($query = mysqli_query($conn, $sql)){
                echo  "<script>alert('Competidor atualizado com sucesso!');</script>";
            }else{
                echo  "<script>alert('Falha ao atualizar competidor no banco!');</script>";
            }
            mysqli_close($conn);
            }
        }
    }
    $conn = mysqli_connect('db', 'user', 'test', "myDb");
    $get_query = "SELECT * FROM Competidor where id = '".$id."'";
    $result = mysqli_query($conn, $get_query);
    $data = $result->fetch_array(MYSQLI_ASSOC);
    $form_name = $data['name'];
    $form_idade = $data['idade'];
    $form_team = $data['team'];
    $form_email = $data['email'];
    $form_cpf = $data['cpf'];
    $form_univ = $data['ie'];
    mysqli_close($conn);
    ?>

<body>
    <div class="container">
    <div class="tab-content">
        <div class="card">
            <div class="card-header">
                <h3 class="well"> Atualizar Competidor </h3>
            </div>
            <div class="card-body">
            
                <form class="form-horizontal" action="" method="POST">
                    <div class="control-group <?php echo !empty($nomeErro) ? 'error' : ''; ?>">
                        <label class="control-label">Nome</label>
                        <div class="controls">
                            <input name="form_name" class="form-control" size="50" type="text" placeholder="Nome"
                                   value="<?php echo !empty($form_name) ? $form_name : ''; ?>">
                            <?php if (!empty($nomeErro)): ?>
                                <span class="text-danger"><?php echo $nomeErro; ?></span>
                            <?php endif; ?>
                        </div>
                    </div>

                    <div class="control-group <?php echo !empty($idadeErro) ? 'error' : ''; ?>">
                        <label class="control-label">Idade</label>
                        <div class="controls">
                            <input name="form_idade" class="form-control" size="50" type="number"
                                   value="<?php echo !empty($form_idade) ? $form_idade : ''; ?>">
                            <?php if (!empty($idadeErro)): ?>
                                <span class="text-danger"><?php echo $idadeErro; ?></span>
                            <?php endif; ?>
                        </div>
                    </div>

                    <div class="control-group <?php echo !empty($timeErro) ? 'error' : ''; ?>">
                        <label class="control-label">Time</label>
                        <div class="controls">
                            <input name="form_team" class="form-control" size="50" type="text"
                                   value="<?php echo !empty($form_team) ? $form_team : ''; ?>">
                            <?php if (!empty($timeErro)): ?>
                                <span class="text-danger"><?php echo $timeErro; ?></span>
                            <?php endif; ?>
                        </div>
                    </div>
                    
                    <div class="control-group <?php echo !empty($emailErro) ? 'error' : ''; ?>">
                        <label class="control-label">Email</label>
                        <div class="controls">
                            <input name="form_email" class="form-control" size="50" type="text"
                                   value="<?php echo !empty($form_email) ? $form_email : ''; ?>">
                            <?php if (!empty($emailErro)): ?>
                                <span class="text-danger"><?php echo $emailErro; ?></span>
                            <?php endif; ?>
                        </div>
                    </div>

                    <?php if ($form_univ == 0): ?>
                        <div class="control-group <?php echo !empty($cpfErro) ? 'error' : ''; ?>">
                            <label class="control-label">CPF</label>
                            <div class="controls">
                                <input name="form_cpf" class="form-control" size="50" type="text"
                                    value="<?php echo !empty($form_cpf) ? $form_cpf : ''; ?>">
                                <?php if (!empty($cpfErro)): ?>
                                    <span class="text-danger"><?php echo $cpfErro; ?></span>
                                <?php endif; ?>
                            </div>
                        </div>
                    <?php endif; ?>
                    <br/>
                    <div class="form-actions">
                        <button id="submit_button" name="submit_button" onsubmit="return false" class="btn btn-warning">Atualizar</button>
                        <a href="index.php" type="btn" class="btn btn-default">Voltar</a>
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>
</body>
</html>