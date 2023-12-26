<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta name="viewport" content="width=device-width", initial-scale="1">
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/main.css"> <!-- main.css가 존재한다면 -->
    <title>DrugBank | <%=request.getAttribute("title")%></title> <!-- 각 페이지별 제목 설정 -->
</head>
<body>
<div class="header">
    <div class="main-nav">
        <div class="logo">
            <a href="main.jsp">
                <div class="logo-flex-container">
                    <img src="image/logo1.jpg" alt="Logo">
                    <div class="logo-texts">
                        <span class="logo-title"> 약 팡 </span>
                        <span class="sublogo-title"> DrugBank </span>
                    </div>
                </div>    
            </a>
        </div>
        <a href="about.jsp">기업소개</a>
        <a href="MDL.jsp">약품정보</a>
        <a href="delivery inquiry.jsp">배송정보</a>
        <a href="headquarters.jsp">지역본부</a>
    </div>
    <!-- 로그인 상태에 따른 버튼 표시 변경 -->
    <% if (session.getAttribute("email") == null) { %>
        <button class="login-button" onclick="location.href='login.jsp'">Login</button>
    <% } else { %>
        <button class="logout-button" onclick="location.href='logoutAction.jsp'">Logout</button>
    <% } %>
</div>
