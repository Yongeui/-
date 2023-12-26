<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width", initial-scale="1" >
<link rel="stylesheet" href="css/bootstrap.css">
<title>Mission Mate | 회원가입</title>
</head>
<body>
   <%@ include file="header.jsp" %>
    
    <div class="container">
        <div class="col-lg-4"></div>
        <div class="col-lg-4">
            <div class ="jumbotron" style="padding-top:20px;">
                <form method = "post" action="joinAction.jsp"> <!-- joinAction 페이지로 화면 넘기기 -->
                    <h3 style="text-align:center;">일반사용자 회원가입</h3>
                    <!-- USER OR GROUP  -->
                    <div class = "form-group">
                    </div>
                     <!-- 성함 -->
                    <div class ="form-group">
                        <input type ="text" class="form-control" placeholder="이름" name ="username" maxlength='20'>
                    </div>
                    <!-- 이메일 -->
                    <div class ="form-group">
                        <input type ="email" class="form-control" placeholder="이메일" name ="email" maxlength='20'>
                    </div>
                     <!-- 비번 -->
                    <div class ="form-group">
                        <input type ="password" class="form-control" placeholder="비밀번호" name ="password" maxlength='20'>
                    </div>
                     <!-- 주소 -->
                     <div class ="form-group">
                        <input type ="address" class="form-control" placeholder="주소" name ="address" maxlength='20'>
                    </div>
                     <!-- 전화번호 -->
                    <div class ="form-group">
                        <input type ="phonenumber" class="form-control" placeholder="전화번호" name ="phonenumber" maxlength='20'>
                    </div>
                    <input type="submit" class="btn btn-primary form-control" value="회원가입">
                </form>
            </div> 
        </div> 
        <div class="col-lg-4"></div>
    </div>
    
    
    <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
    <script src="js/bootstrap.js"></script>
</body>
</html>