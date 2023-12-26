<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="Mdl.MdlDAO" %>
<%@ page import="java.io.PrintWriter" %>
<% request.setCharacterEncoding("UTF-8"); %>

<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>DrugBank | 약품 정보 저장</title>
</head>
<body>
    <%
        String email = null;
        if (session.getAttribute("email") != null) {
            email = (String) session.getAttribute("email");
        }
        String selectedDrugType = request.getParameter("selectedDrugType");

        if (email == null || selectedDrugType == null || selectedDrugType.isEmpty()) {
            PrintWriter script = response.getWriter();
            script.println("<script>");
            script.println("alert('로그인 및 약품 분류 선택이 필요합니다.');");
            script.println("history.back();");
            script.println("</script>");
        } else {
            String manufactureID = request.getParameter("manufactureID");
            String medicationname = request.getParameter("medicationname");
            String category = request.getParameter("category");
            String price = request.getParameter("price");
            String strength = request.getParameter("strength");

            MdlDAO mdlDAO = new MdlDAO();
            int result = -1;
            if (selectedDrugType.equals("OTC")) {
                result = mdlDAO.writeOTC(manufactureID, medicationname, category, price, strength);
            } else if (selectedDrugType.equals("PM")) {
                result = mdlDAO.writePM(manufactureID, medicationname, category, price, strength);
            }

            if (result == -1) {
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('정보 저장에 실패했습니다.');");
                script.println("history.back();");
                script.println("</script>");
            } else {
                PrintWriter script = response.getWriter();
                script.println("<script>");
                script.println("alert('정보가 저장되었습니다.');");
                script.println("location.href = 'bbs.jsp';");
                script.println("</script>");
            }
        }
    %>
</body>
</html>
