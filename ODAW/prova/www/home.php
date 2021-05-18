<html>
 <head>
  <title>Controle Despesas</title>

  <meta charset="utf-8"> 

  <link rel="stylesheet" href="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js"></script>

</head>
<body>
    <?php 
        $tipo_mapping = array(
            0 => "Fixa",
            1 => "Comida",
            2 => "Decoração",
            3 => "Roupas",
            4 => "Outra"
        );
    ?>

    <div class="container">

    <div class="tab-content">
        <form class="form-horizontal" action="" method="POST">
            <fieldset>
            <div class="card">
                <div class="card-header">
                    <h3 class="well"> Cadastrar Despesa </h3>
                </div>
            </div>

            <!-- Text input-->
            <div class="form-group">
            <label class="col-md-4 control-label" for="desc_field">Descrição</label>  
            <div class="col-md-4">
            <input id="desc_field" name="desc_field" type="text" placeholder="Descreva a despesa..." class="form-control input-md" required>
            
            </div>
            </div>
            
            <div class="form-group">
            <label class="col-md-4 control-label" for="valor_field">Valor</label>  
            <div class="col-md-4">
            <input id="valor_field" name="valor_field" type="currency" class="form-control input-md" value="123.5" required>
            </div>
            </div>
                
            <div class="form-group">
            <label class="col-md-4 control-label" for="mult_field">Quantidade</label>  
            <div class="col-md-4">
            <input id="mult_field" value="1" name="mult_field" type="number" placeholder="Multiplicador" class="form-control input-md" required="">
                
            </div>
            </div>

            
            <!-- Multiple Radios -->
            <div class="form-group">
            <label class="col-md-4 control-label" for="tipo_field">Tipo despesa</label>
            <div class="col-md-4">
            <div class="radio">
                <label for="tipo_field-0">
                <input type="radio" name="tipo_field" id="tipo_field-0" value="0" checked="checked">
                Fixa
                </label>
                </div>
            <div class="radio">
                <label for="tipo_field-1">
                <input type="radio" name="tipo_field" id="tipo_field-1" value="1">
                Comida
                </label>
                </div>
            <div class="radio">
                <label for="tipo_field-2">
                <input type="radio" name="tipo_field" id="tipo_field-2" value="2">
                Decoração
                </label>
                </div>
            <div class="radio">
                <label for="tipo_field-3">
                <input type="radio" name="tipo_field" id="tipo_field-3" value="3">
                Roupas
                </label>
                </div>
            <div class="radio">
                <label for="tipo_field-4">
                <input type="radio" name="tipo_field" id="tipo_field-4" value="4">
                Outros
                </label>
                </div>
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
                    <h3 class="well"> Listagem de Despesas </h3>
                </div>
            </div>

            <?php

            if(isset($_POST["submit_button"])){



                $form_desc = $_POST['desc_field'];
                $form_valor = preg_replace('/[^0-9.-]+/','', $_POST['valor_field']);
                $form_valor = $form_valor * $_POST['mult_field'];
                $form_tipo = $_POST['tipo_field'];

                if(strcmp($feedback, "") == 0){
                    $conn = mysqli_connect('db', 'user', 'test', "avaliacaoODAW");
                    if($query = mysqli_query(
                        $conn,
                        "INSERT INTO `despesa` (`descricao`, `valor`, `tipo`) VALUES
                        ('".$form_desc."', '".$form_valor."', '".$form_tipo."')")){
                            echo  "<script>alert('Despesa cadastrada com sucesso!');</script>";
                        }else{
                            echo  "<script>alert('Falha ao registrar despesa no banco!');</script>";
                    }
                    mysqli_close($conn);
                } else {
                    echo  "<script>alert('" . $feedback . "');</script>";
                }
            }
            ?>
        
       
            <?php
                $conn = mysqli_connect('db', 'user', 'test', "avaliacaoODAW");
                
                $list_query = "SELECT * From `despesa`";
                $result = mysqli_query($conn, $list_query);
                $soma = 0;

                echo '<table class="table table-striped">';
                echo '<thead><tr><th>Descrição</th><th>Valor</th><th>Tipo</th></tr></thead>';
                while($value = $result->fetch_array(MYSQLI_ASSOC)){
                    echo '<tr>';
                    echo '<td>' . $value['descricao'] . '</td>';
                    echo '<td>' . $value['valor'] . '</td>';
                    echo '<td>' . $tipo_mapping[$value['tipo']] . '</td>';
                    $soma += $value['valor'];
                }
                echo '<thead><tr><th>Balanço</th><th>'.$soma.'</th><th></th></tr></thead>';
                echo '</table>';

                $result->close();

                mysqli_close($conn);

            ?>
        </div>
        </div>
    </div>
</body>

<script>

        var valorInput = document.querySelector('input[type="currency"]')

        onBlur({target:valorInput})

        valorInput.addEventListener('focus', onFocus)
        valorInput.addEventListener('blur', onBlur)


        function localStringToNumber( s ){
        return Number(String(s).replace(/[^0-9.-]+/g,""))
        }

        function onFocus(e){
        var value = e.target.value;
        e.target.value = value ? localStringToNumber(value) : ''
        }

        function onBlur(e){
        var value = e.target.value

        var options = {
            maximumFractionDigits : 2,
            currency              : 'BRL', // https://www.currency-iso.org/dam/downloads/lists/list_one.xml
            style                 : "currency",
            currencyDisplay       : "symbol"
        }
        
        e.target.value = (value || value === 0) 
            ? localStringToNumber(value).toLocaleString(undefined, options)
            : ''
        }

    </script>

</html>
