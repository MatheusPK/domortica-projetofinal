// Initialize Firebase
var config = {
  apiKey: "AIzaSyBkPN5Uzu_TnRlXCxnO1Ac0YTz2JkicGPA",
  authDomain: "casa-automatica-86bff.firebaseapp.com",
  databaseURL: "https://casa-automatica-86bff.firebaseio.com",
  projectId: "casa-automatica-86bff",
  storageBucket: "casa-automatica-86bff.appspot.com",
  messagingSenderId: "552042836113"
};
firebase.initializeApp(config);

function login(){
  $("#txtUsuario").hide();
  $("#btnCriarConta").hide();
  $("#btnLogin").show();
  $("#labelNome").hide();
  $("#linkSign").html("Não tem uma conta? <a href='#' onclick='novaConta()'>Criar Conta</a>")
  $("#title").text("Logar");
  $("#botaoSubmit").text("Entrar");
  $("#botaoSubmit").attr("onclick", "logar()");
}

function novaConta() {
  $("#txtUsuario").show();
  $("#btnCriarConta").show();
  $("#btnLogin").hide();
  $("#labelNome").show();
  $("#linkSign").html("Já tem um conta? <a href='#' onclick='login()'>Logar</a>")
  $("#title").text("Criar Conta");
  $("#botaoSubmit").text("Criar");
  $("#botaoSubmit").attr("onclick", "criarConta()");
}

function logar(){
    const email = $("#txtEmail").val();
    const senha = $("#txtSenha").val();
    const auth = firebase.auth();
    const promise = auth.signInWithEmailAndPassword(email, senha);
    promise.then(e => location.href = "viewCasaLogado.html");
    promise.catch(e => alert(" " + e.message));
}

function criarConta(){
    const usuario = $("#txtUsuario").val();
    if(usuario === "") {
      alert("Insira um nome")
      return;
    }
    const email = $("#txtEmail").val();
    const senha = $("#txtSenha").val();
    const auth = firebase.auth();
    const promise = auth.createUserWithEmailAndPassword(email, senha);
    promise.then(e => e.updateProfile({ displayName: usuario}));
    promise.then(e => alert("Conta criada"));
    promise.then(e => login());
    promise.catch(e => alert(" " + e.message));
}

