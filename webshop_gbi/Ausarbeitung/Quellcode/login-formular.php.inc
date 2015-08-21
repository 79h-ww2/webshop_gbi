<!-- JavaScript zur Überprüfung der Eingabe wird zur Webseite imporiert -->
<script type="text/javascript" 
    src="./Funktions/JS/vorcheck_std_funktionen.js" >
</script>
<script type="text/javascript" src="./Funktions/JS/anmeldung.js" >
</script>

<form method="post" action="..." name="form_login" id="login" 
    onsubmit="return vorcheckEingabe_anmeldung('form_login');">
            
    <!-- Textfeld zur Eingabe der Login-Email-Adresse -->
    <label for="anmedlung_email">Email:</label> 
    <input type="text" name="anmedlung_email" maxlength="50" 
        class="lang_reg" />
        
    <!-- Textfeld zur Eingabe des Passworts -->
    <label for="anmedlung_passwort">Passwort:</label> 
    <input type="password" name="anmedlung_passwort" maxlength="50" 
        class="lang_reg" />
        
        
    <!-- Fehlermeldungen bei ungültiger Eingabe -->
    <p class="text_fehlermeldung" id="fehlermeldung_login">
        <?php /* Fehlermeldungstext */ ?>
    </p>

    <!-- Der Submit-Buttton -->
    <input type="submit"  value="Login" title="Login"/>
</form>
