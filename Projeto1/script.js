// Realiza um disparo via AJAX para o endereço do meu NodeMCU
var led_controle = function(status){
    var xmlhttp = new XMLHttpRequest();
    var set_status = "http://192.168.18.25/?function=" + status;
    xmlhttp.open("GET", set_status);
    xmlhttp.send();
}

//Acessa os botões e passando as novas diretivas de ligar ou desligar o led
var led = function() {
    var ligar = document.querySelector(".ligar");
        ligar.onclick = function(){
            led_controle("led4_on");
            console.log("led4_on");
        }

    var desligar = document.querySelector(".desligar");
        desligar.onclick = function(){
            led_controle("led4_off");
            console.log("led4_off");
        }
}

windows.onload = function(){
    //Chama a função led
    led();
}