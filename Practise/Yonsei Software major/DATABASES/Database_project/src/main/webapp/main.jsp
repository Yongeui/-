<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ include file="header.jsp" %>

<div class="hero-section" id="mainContent">
    <img src="image/tit_sec01.png" alt="Introduction" class="title-image">
    <div class="search-area">
        <div class="search-bg">
            <img src="image/main_search_bg.jpg" alt="Search Background" class="bg-image">
            <div class="search-box">
                <img src="image/main_search_icon.jpg" alt="Search Icon" class="search-icon">
            </div>
        </div>
        <div class="med-buttons">
            <a href="MDL.jsp?type=OTC">
    <img src="image/main_search_btn2.jpg" alt="General Medicine" class="med-button-img">
			</a>
			<a href="MDL.jsp?type=PM">
    <img src="image/main_search_btn1.jpg" alt="Prescription Medicine" class="med-button-img">
			</a>
<img src="image/main_search_btn3.jpg" alt="Related Sites" class="med-button-img" onclick="showRelatedSites()">

        </div>
    </div>
</div>

<!-- 관련사이트 팝업 -->
<div id="relatedSitesPopup" class="related-sites-popup" style="display: none;">
    <div class="popup-content">
        <a href="https://go.drugbank.com/" target="_blank">DrugBank</a>
        <a href="https://www.data.go.kr/index.do" target="_blank">공공데이터포털</a>
        <a href="https://hudc.seoulmc.or.kr/" target="_blank">서울시민 건강포털</a>
        <button class="close-btn" onclick="hideRelatedSites()">X</button>
    </div>
</div>

<%@ include file="footer.jsp" %>

<script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
<script src="js/bootstrap.js"></script>
<script>
    function showRelatedSites() {
        document.getElementById('relatedSitesPopup').style.display = 'block';
    }

    function hideRelatedSites() {
        document.getElementById('relatedSitesPopup').style.display = 'none';
    }
</script>
</body>
</html>
