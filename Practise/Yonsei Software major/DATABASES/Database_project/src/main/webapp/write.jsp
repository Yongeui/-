<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.io.PrintWriter" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta name="viewport" content="width=device-width", initial-scale="1">
    <link rel="stylesheet" href="css/bootstrap.css">
    <title>DrugBank | 약품 정보 등록</title>
    <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
    <script>
        $(document).ready(function() {
            $("#drugTypeSelect").hide();

            $("#drugCategoryBtn").click(function() {
                $("#drugTypeSelect").slideToggle();
            });
        });
    </script>
</head>
<body>
    <%@ include file="header.jsp" %>
    <div class="container">
        <div class="row">
            <h2>약품 정보 등록</h2>
            <button id="drugCategoryBtn" class="btn btn-info">약품 분류</button>
            <div id="drugTypeSelect">
                <div><input type="radio" name="drugType" value="OTC"> OTC약품</div>
                <div><input type="radio" name="drugType" value="PM"> PM약품</div>
            </div>
            <form method="post" action="writeAction.jsp">
                <input type="hidden" name="selectedDrugType" value="">
                <table class="table">
                    <!-- Form Fields -->
                    <tr><td><input type="text" class="form-control" placeholder="제조업체 ID" name="manufactureID"></td></tr>
                    <tr><td><input type="text" class="form-control" placeholder="약품명" name="medicationname"></td></tr>
                    <tr><td><input type="text" class="form-control" placeholder="카테고리" name="category"></td></tr>
                    <tr><td><input type="text" class="form-control" placeholder="가격" name="price"></td></tr>
                    <tr><td><input type="text" class="form-control" placeholder="함량" name="strength"></td></tr>
                </table>
                <input type="submit" class="btn btn-success" value="저장하기">
            </form>
        </div>
    </div>
    <%@ include file="footer.jsp" %>
    <script>
        $('input[type="radio"][name="drugType"]').change(function() {
            $('input[name="selectedDrugType"]').val(this.value);
        });
    </script>
</body>
</html>
