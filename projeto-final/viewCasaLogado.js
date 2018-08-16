var config = {
    apiKey: "AIzaSyBkPN5Uzu_TnRlXCxnO1Ac0YTz2JkicGPA",
    authDomain: "casa-automatica-86bff.firebaseapp.com",
    databaseURL: "https://casa-automatica-86bff.firebaseio.com",
    projectId: "casa-automatica-86bff",
    storageBucket: "casa-automatica-86bff.appspot.com",
    messagingSenderId: "552042836113"
};
firebase.initializeApp(config);

firebase.auth().onAuthStateChanged(function(user) {
    if (user) {
        if(firebase.auth().currentUser.photoURL != null) {
            $(".useravatar").children().attr("src", firebase.auth().currentUser.photoURL);
            $(".card-background").children().attr("src", firebase.auth().currentUser.photoURL);
        }
        $("#userName").text(firebase.auth().currentUser.displayName);
    }
});

function sair(){
    firebase.auth().signOut().then(e => location.href = "viewCasaLogin.html").catch(e => console.log("catch login", e.message));
}

const quartoLed = firebase.database().ref('quartoLed');
const banheiroLed = firebase.database().ref('banheiroLed');
const cozinhaLed = firebase.database().ref('cozinhaLed');
const salaLed = firebase.database().ref('salaLed');
const Temperatura = firebase.database().ref('Temperatura');

quartoLed.on('value', valor => {
    $("#quartoLed").text(valor.val());
});

banheiroLed.on('value', valor => {
    $("#banheiroLed").text(valor.val());
});

cozinhaLed.on('value', valor => {
    $("#cozinhaLed").text(valor.val());
});

salaLed.on('value', valor => {
    $("#salaLed").text(valor.val());
});

Temperatura.on('value', valor => {
    $("#Temperatura").text(valor.val());
});

function ligarLed(elemento) {
    dbRef = $(elemento).parent().prev().attr("id");
    console.log(elemento);
    firebase.database().ref(dbRef).set("ligada");
}

function desligarLed(elemento) {
    dbRef = $(elemento).parent().prev().attr("id");
    firebase.database().ref(dbRef).set("desligada");
}

function alterarFoto() {
    var imagemURL = prompt("Insira a url da imagem que se tornará sua foto de perfil");
    var img = '<img src="'+ imagemURL +'" />';
    $(img).on('load', function(){
        firebase.auth().currentUser.updateProfile({photoURL: imagemURL});
        $(".useravatar").children().attr("src", imagemURL);
        $(".card-background").children().attr("src", imagemURL);
    });
}
 