<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.io.PrintWriter" %>
<%@ page import="Mdl.MdlDAO" %>
<%@ page import="Mdl.MDL" %>
<%@ page import="java.util.ArrayList" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta name="viewport" content="width=device-width", initial-scale="1">
    <link rel="stylesheet" href="css/bootstrap.css">
    <title>DrugBank | Medication List</title>
</head>
<body>
    <%@ include file="header.jsp" %>
    <div class="container">
        <div class="row">
            <h2>Medication List</h2>
            <table class="table table-striped">
                <thead>
                    <tr>
                        <th style="text-align: center;">번호</th>
                        <th style="text-align: center;">약품이름</th>
                        <th style="text-align: center;">카테고리</th>
                        <th style="text-align: center;">가격</th>
                    </tr>
                </thead>
                <tbody>
                    <%
                        String type = request.getParameter("type");
                        int pageNumber = 1;
                        if (request.getParameter("pageNumber") != null) {
                            pageNumber = Integer.parseInt(request.getParameter("pageNumber"));
                        }
                        MdlDAO mdlDAO = new MdlDAO();
                        ArrayList<MDL> list;
                        if (type == null) {
                            list = mdlDAO.getMedicationList(pageNumber);
                        } else if ("OTC".equals(type)) {
                            list = mdlDAO.getOTCMedicationList(pageNumber);
                        } else { // "PM".equals(type)
                            list = mdlDAO.getPMMedicationList(pageNumber);
                        }
                        for (MDL mdl : list) {
                    %>
                    <tr>
                        <td><%= (pageNumber - 1) * 30 + list.indexOf(mdl) + 1 %></td>
                        <td><%= mdl.getMedicationName() %></td>
                        <td><%= mdl.getCategory() %></td>
                        <td><%= mdl.getPrice() %></td>
                    </tr>
                    <%
                        }
                    %>
                </tbody>
            </table>

            <div style="text-align: center;">
                <%
                    int totalItems;
                    if ("OTC".equals(type)) {
                        totalItems = mdlDAO.getTotalOTCItems();
                    } else if ("PM".equals(type)) {
                        totalItems = mdlDAO.getTotalPMItems();
                    } else {
                        totalItems = mdlDAO.getTotalItems();
                    }
                    int itemsPerPage = 30;
                    int totalPages = (int) Math.ceil((double) totalItems / itemsPerPage);

                    if (pageNumber > 1) {
                %>
                        <a href="MDL.jsp?type=<%= type %>&pageNumber=<%= pageNumber - 1 %>">&lt; Previous</a>
                <%
                    }
                    for (int i = 1; i <= totalPages; i++) {
                %>
                        <a href="MDL.jsp?type=<%= type %>&pageNumber=<%= i %>"><%= i %></a>
                <%
                    }
                    if (pageNumber < totalPages) {
                %>
                        <a href="MDL.jsp?type=<%= type %>&pageNumber=<%= pageNumber + 1 %>">Next &gt;</a>
                <%
                    }
                %>
            </div>
        </div>
    </div>
    <%@ include file="footer.jsp" %>
    <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
    <script src="js/bootstrap.js"></script>
</body>
</html>
