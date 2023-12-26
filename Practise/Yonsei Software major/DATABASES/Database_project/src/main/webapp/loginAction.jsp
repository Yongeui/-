<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import = "User.UserDAO" %>
<%@ page import = "java.io.PrintWriter" %>
<% request.setCharacterEncoding("UTF-8"); %>
 
<jsp:useBean id="user" class="User.User" scope="page"></jsp:useBean>
<jsp:setProperty name="user" property="email"/>
<jsp:setProperty name="user" property="password"/>
 
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>JSP BBS</title>
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
        else{
        	UserDAO userDAO = new UserDAO();
            int result = userDAO.login(user.getemail(), user.getpassword());
            if (result == 1){
            	session.setAttribute("email", user.getemail());
            	out.println("<script>alert('로그인에 성공하였습니다.'); location.href='main.jsp';</script>");
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("location.href = 'main.jsp'");
                script.println("</script>");
            }
            else if (result == 0){
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('비밀번호가 틀립니다.')");
                script.println("history.back()");    // 이전 페이지로 사용자를 보냄
                script.println("</script>");
            }
            else if (result == -1){
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('존재하지 않는 아이디입니다.')");
                script.println("history.back()");    // 이전 페이지로 사용자를 보냄
                script.println("</script>");
            }
            else if (result == -2){
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('DB 오류가 발생했습니다.')");
                script.println("history.back()");    // 이전 페이지로 사용자를 보냄
                script.println("</script>");
            }
        }
    %>
 
</body>
</html>