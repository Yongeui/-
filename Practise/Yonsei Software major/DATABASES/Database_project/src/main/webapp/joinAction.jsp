<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "User.UserDAO" %>
<%@ page import = "java.io.PrintWriter" %>
<% request.setCharacterEncoding("UTF-8"); %>
 
<jsp:useBean id="user" class="User.User" scope="page"></jsp:useBean>
<jsp:setProperty name="user" property="username"/>
<jsp:setProperty name="user" property="email"/>
<jsp:setProperty name="user" property="password"/>
<jsp:setProperty name="user" property="address"/>
<jsp:setProperty name="user" property="phonenumber"/>
 
<head>
<meta http-equiv="Content-Type" content="text/html; c harset=UTF-8">
<title>JSP USER_DB</title>
</head>
<body>
    <%  
    	String email = null;
		if (session.getAttribute("email") != null){
        	email = (String) session.getAttribute("email");
		}
		if (email != null){
        	PrintWriter script = response.getWriter();
        	script.println("<script>");
        	script.println("alert('이미 로그인되었습니다.')");
        	script.println("location.href = 'main.jsp'");    // 메인 페이지로 이동
        	script.println("</script>");
		}
    	if (user.getusername() == null || user.getemail() == null || user.getpassword() == null 
    		|| user.getaddress() == null || user.getphonenumber() == null){
    		PrintWriter script = response.getWriter();
            script.println("<script>");
            script.println("alert('모든 문항을 입력해주세요.')");
            script.println("history.back()");    // 이전 페이지로 사용자를 보냄
            script.println("</script>");
    	}else{
    		UserDAO userDAO = new UserDAO();
            int result = userDAO.join(user);
            if (result == -1){ // 회원가입 실패시
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('이미 존재하는 ID 입니다.')");
                script.println("history.back()");    // 이전 페이지로 사용자를 보냄
                script.println("</script>");
            }else{ // 회원가입 성공시
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('회원가입이 완료되었습니다.');");
                script.println("location.href = 'main.jsp'");    // 메인 페이지로 이동
                script.println("</script>");
            }
    	}
    %>
 
</body>
</html>