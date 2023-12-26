<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta name="viewport" content="width=device-width", initial-scale="1">
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/login.css">
    <title>DrugBank | 로그인</title>
</head>
<body>
    <%@ include file="header.jsp" %>

    <div class="hero-section">
        <div class="container">
            <div class="row justify-content-center align-items-center" style="height: 100vh;">
                <div class="col-lg-6">
                    <div class="jumbotron">
                        <div class="login-header">로그인</div>
                        <form method="post" action="loginAction.jsp" class="login-form">
                            <div class="sec1">
                                <input type="email" class="form-control" placeholder="이메일" name="email" maxlength="20">
                                <input type="password" class="form-control" placeholder="비밀번호" name="password" maxlength="20">
                                <button type="submit" class="btn btn-primary">로그인</button>
                            </div>
                            <div class="sec2 checkbox-group">
                                <input type="checkbox" id="rememberMe">
                                <label for="rememberMe">아이디 저장</label>
                            </div>
                            <hr>
                            <div class="sec3 additional-links">
                                <a href="join.jsp" class="btn btn-secondary">회원가입</a>
                                <a href="findId.jsp" class="btn btn-secondary" id="find-id">아이디 찾기</a>
                                <a href="findPassword.jsp" class="btn btn-secondary" id="find-password">비밀번호 찾기</a>
                            </div>
                        </form>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <%@ include file="footer.jsp" %>

    <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
    <script src="js/bootstrap.js"></script>
</body>
</html>
