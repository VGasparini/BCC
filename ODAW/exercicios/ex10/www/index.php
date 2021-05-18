<html>
 <head>
  <title>BRUTE</title>

  <meta charset="utf-8"> 

  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>

</head>
<body>
    <?php 
        $ies_mapping = array(
            0 => "UDESC",
            1 => "UNIVILLE",
            2 => "UNISOCIESC",
            3 => "PUC",
            4 => "Outra"
        );

        function checkFields($idade, $email, $cpf){
            $feedback = "";
            if ($idade > 100){
                $feedback .= "Idade excede limite de 100 anos -";
            }
            if(!preg_match('/^\S+@\S+\.\S+$/', $email)){
                $feedback .= " Email invalido -";
            }
            if(strlen(preg_replace( '/[^0-9]/is', '', $cpf)) == 11){
                for ($t = 9; $t < 11; $t++) {
                    for ($d = 0, $c = 0; $c < $t; $c++) {
                        $d += $cpf[$c] * (($t + 1) - $c);
                    }
                    $d = ((10 * $d) % 11) % 10;
                    if ($cpf[$c] != $d) {
                        $feedback .= " CPF invalido -";
                    }
                }
            } else {
                $feedback .= " CPF invalido -";
            }

            return $feedback;
        }
    ?>
    <div class="container">

    <div class="tab-content">
        <form class="form-horizontal" action="" method="POST">
            <fieldset>
            <div class="card">
                <div class="card-header">
                    <h3 class="well"> Cadastrar Competidor </h3>
                </div>
            </div>

            <!-- Text input-->
            <div class="form-group">
            <label class="col-md-4 control-label" for="name_field">Nome</label>  
            <div class="col-md-4">
            <input id="name_field" name="name_field" type="text" placeholder="Insira seu nome..." class="form-control input-md" required="">
            
            </div>
            </div>
            
            <div class="form-group">
            <label class="col-md-4 control-label" for="idade_field">Idade</label>  
            <div class="col-md-4">
            <input id="idade_field" name="idade_field" type="number" class="form-control input-md" required="">
                
            </div>
            </div>

            <!-- Text input-->
            <div class="form-group">
            <label class="col-md-4 control-label" for="team_field">Time</label>  
            <div class="col-md-4">
            <input id="team_field" name="team_field" type="text" placeholder="Insira nome do seu time..." class="form-control input-md" required="">
                
            </div>
            </div>

            <!-- Multiple Radios -->
            <div class="form-group">
            <label class="col-md-4 control-label" for="univ_field">Universidade</label>
            <div class="col-md-4">
            <div class="radio">
                <label for="univ_field-0">
                <input type="radio" name="univ_field" id="univ_field-0" value="0" checked="checked">
                UDESC
                </label>
                </div>
            <div class="radio">
                <label for="univ_field-1">
                <input type="radio" name="univ_field" id="univ_field-1" value="1">
                UNIVILLE
                </label>
                </div>
            <div class="radio">
                <label for="univ_field-2">
                <input type="radio" name="univ_field" id="univ_field-2" value="2">
                UNISOCIESC
                </label>
                </div>
            <div class="radio">
                <label for="univ_field-3">
                <input type="radio" name="univ_field" id="univ_field-3" value="3">
                PUC
                </label>
                </div>
            <div class="radio">
                <label for="univ_field-4">
                <input type="radio" name="univ_field" id="univ_field-4" value="4">
                Outros
                </label>
                </div>
            </div>
            </div>

            <!-- Text input-->
            <div class="form-group">
            <label class="col-md-4 control-label" for="email_field">Email</label>  
            <div class="col-md-4">
            <input id="email_field" name="email_field" type="text" placeholder="Insira seu email..." class="form-control input-md">
                
            </div>
            </div>

            <!-- Text input-->
            <div class="form-group">
            <label class="col-md-4 control-label" for="cpf_field">CPF</label>  
            <div class="col-md-4">
            <input id="cpf_field" name="cpf_field" type="text" placeholder="Insira seu CPF" class="form-control input-md">
            <span class="help-block">* Somente para estudantes da UDESC</span>  
            </div>
            </div>

            <!-- Button -->
            <div class="form-group">
            <label class="col-md-4 control-label" ></label>
            <div class="col-md-4">
                <button id="submit_button" name="submit_button" onsubmit="return false" class="btn btn-primary">Adicionar</button>
            </div>
            </div>

            </fieldset>
            </form>

            </div>

            <div class="card">
                <div class="card-header">
                    <h3 class="well"> Listagem de Competidores </h3>
                </div>
            </div>

            <?php

            if(isset($_POST["submit_button"])){
                $form_name = $_POST['name_field'];
                $form_idade = $_POST['idade_field'];
                $form_team = $_POST['team_field'];
                $form_univ = $_POST['univ_field'];
                $form_email = $_POST['email_field'];
                $form_cpf = $_POST['cpf_field'];

                $feedback = checkFields($form_idade, $form_email, $form_cpf);
            
                if(strcmp($feedback, "") == 0){
                    $conn = mysqli_connect('db', 'user', 'test', "myDb");
                    if($query = mysqli_query(
                        $conn,
                        "INSERT INTO `Competidor` (`name`, `idade`, `team`, `ie`, `email`, `cpf`) VALUES
                        ('".$form_name."', '".$form_idade."', '".$form_team."', '".$form_univ."', '".$form_email."', '".$form_cpf."')")){
                            echo  "<script>alert('Competidor cadastrado com sucesso!');</script>";
                        }else{
                            echo  "<script>alert('Falha ao registrar competidor no banco!');</script>";
                    }
                    mysqli_close($conn);
                } else {
                    echo  "<script>alert('" . $feedback . "');</script>";
                }
            }
            ?>
        
       
            <?php

                $conn = mysqli_connect('db', 'user', 'test', "myDb");
                
                $list_query = 'SELECT * From Competidor';
                $result = mysqli_query($conn, $list_query);

                echo '<table class="table table-striped">';
                echo '<thead><tr><th>Nome</th><th>Idade</th><th>Time</th><th>Email</th><th>Instituição</th><th>CPF</th><th>Ação</th></tr></thead>';
                while($value = $result->fetch_array(MYSQLI_ASSOC)){
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
                    echo '<td width=250>';
                    echo '<a class="btn btn-warning" href="update.php?id='.$value['id'].'">Atualizar</a>';
                    echo ' ';
                    echo '<a class="btn btn-danger" href="delete.php?id='.$value['id'].'">Excluir</a>';
                    echo '</td>';
                    echo '</tr>';
                }
                echo '</table>';

                $result->close();

                mysqli_close($conn);

            ?>
        </div>
        </div>
    </div>
</body>
</html>
