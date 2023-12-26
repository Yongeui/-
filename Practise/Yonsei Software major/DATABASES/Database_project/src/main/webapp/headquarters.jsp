<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta name="viewport" content="width=device-width", initial-scale="1">
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/custom.css">
    <title>DrugBank | ABOUT</title>
</head>
<body>
<% 
    String email = null;
    if (session.getAttribute("email") != null){
        email = (String) session.getAttribute("email");
    }
    %>
    <%@ include file="header.jsp" %>

    <!-- 페이지의 내용 -->

    <%@ include file="footer.jsp" %>
</body>
</html>
