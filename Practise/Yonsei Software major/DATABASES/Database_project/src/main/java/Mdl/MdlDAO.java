package Mdl;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

public class MdlDAO {
    private Connection conn;
    private ResultSet rs;

    public MdlDAO() {
        try {
            String dbURL = "jdbc:mariadb://localhost:3306/drugbank";
            String dbID = "root";
            String dbPassword = "sw701020";
            Class.forName("org.mariadb.jdbc.Driver");
            conn = DriverManager.getConnection(dbURL, dbID, dbPassword);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


 // OTC 테이블에 데이터를 저장하는 메서드
    public int writeOTC(String manufactureID, String medicationname, String category, String price, String strength) {
        String SQL = "INSERT INTO OTC (manufactureid, medicationname, category, price, strength) VALUES (?, ?, ?, ?, ?)";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            pstmt.setString(1, manufactureID);
            pstmt.setString(2, medicationname);
            pstmt.setString(3, category);
            pstmt.setString(4, price);
            pstmt.setString(5, strength);
            return pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // DB 오류
    }

    // PM 테이블에 데이터를 저장하는 메서드
    public int writePM(String manufactureID, String medicationname, String category, String price, String strength) {
        String SQL = "INSERT INTO PM (manufactureid, medicationname, category, price, strength) VALUES (?, ?, ?, ?, ?)";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            pstmt.setString(1, manufactureID);
            pstmt.setString(2, medicationname);
            pstmt.setString(3, category);
            pstmt.setString(4, price);
            pstmt.setString(5, strength);
            return pstmt.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1; // DB 오류
    }
    public ArrayList<MDL> getMedicationList(int pageNumber) {
        int start = (pageNumber - 1) * 80;
        String SQL = "SELECT medicationname, category, price FROM OTC UNION SELECT medicationname, category, price FROM PM LIMIT ?, 30";
        ArrayList<MDL> list = new ArrayList<MDL>();
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, start);
            rs = pstmt.executeQuery();
            while (rs.next()) {
                MDL mdl = new MDL();
                mdl.setMedicationName(rs.getString("medicationname"));
                mdl.setCategory(rs.getString("category"));
                mdl.setPrice(rs.getString("price"));
                list.add(mdl);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return list;
    }

    public int getTotalItems() {
        String SQL = "SELECT COUNT(*) FROM (SELECT medicationname FROM OTC UNION ALL SELECT medicationname FROM PM) AS combined";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
    // 기존 메서드들...

    // OTC 약품 리스트를 가져오는 메서드
    public ArrayList<MDL> getOTCMedicationList(int pageNumber) {
        ArrayList<MDL> list = new ArrayList<MDL>();
        String SQL = "SELECT * FROM OTC LIMIT ?";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, (pageNumber - 1) * 30);
            rs = pstmt.executeQuery();
            while (rs.next()) {
                MDL mdl = new MDL();
                // 데이터 추출 및 MDL 객체에 설정
                mdl.setMedicationName(rs.getString("medicationName"));
                mdl.setCategory(rs.getString("category"));
                mdl.setPrice(rs.getString("price"));
                list.add(mdl);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return list;
    }

    // PM 약품 리스트를 가져오는 메서드
    public ArrayList<MDL> getPMMedicationList(int pageNumber) {
        ArrayList<MDL> list = new ArrayList<MDL>();
        String SQL = "SELECT * FROM PM LIMIT ?, 30"; // 가상의 SQL 쿼리
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, (pageNumber - 1) * 30);
            rs = pstmt.executeQuery();
            while (rs.next()) {
                MDL mdl = new MDL();
                // 데이터 추출 및 MDL 객체에 설정
                mdl.setMedicationName(rs.getString("medicationName"));
                mdl.setCategory(rs.getString("category"));
                mdl.setPrice(rs.getString("price"));
                list.add(mdl);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return list;
    }

    // OTC 약품의 총 수를 반환하는 메서드
    public int getTotalOTCItems() {
        String SQL = "SELECT COUNT(*) FROM OTC"; // 가상의 SQL 쿼리
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    // PM 약품의 총 수를 반환하는 메서드
    public int getTotalPMItems() {
        String SQL = "SELECT COUNT(*) FROM PM"; // 가상의 SQL 쿼리
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
}