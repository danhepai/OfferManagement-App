//
// Created by dan gaspar on 02.04.2024.
//

#include "../headers/tests.h"
#include "../headers/FileRepository.h"
#include <cassert>
#include <iostream>
#include <sstream>

void test_Offer(){
    Offer off{"Oferta", "Cluj", "Urban", 100};
    assert(off.getName() == "Oferta");
    assert(off.getDestination() == "Cluj");
    assert(off.getType() == "Urban");
    assert(off.getPrice() == 100);
}

void test_Validator(){
    OfferValidator val{};
    Offer off{"", "Cluj", "Urban", 100};
    try{
        val.validate(off);
        assert(false);
    }
    catch (ValidatorException &ex){
        assert(true);
    }
    Offer off2{"Oferta", "", "Urban", 100};
    try{
        val.validate(off2);
        assert(false);
    }
    catch (ValidatorException &ex){
        assert(true);
    }
    Offer off3{"Oferta", "Cluj", "", 100};
    try{
        val.validate(off3);
        assert(false);
    }
    catch (ValidatorException &ex){
        assert(true);
    }
    Offer off4{"Oferta", "Cluj", "Urban", -100};
    try{
        val.validate(off4);
        assert(false);
    }
    catch (ValidatorException &ex){
        assert(true);
    }
    Offer off5{"Oferta", "Cluj", "Urban", 100};
    try{
        val.validate(off5);
        assert(true);
    }
    catch (ValidatorException &ex){
        assert(false);
    }

    std::ostringstream oss;
    ValidatorException ex("Test message");
    oss << ex;
    assert(oss.str() == "Test message");
}

void test_Repository(){
    OffersRepo repo{};
    Offer off{"Oferta", "Cluj", "Urban", 100};
    repo.repo_addOffer(off);
    assert(repo.repo_findOffer("Oferta").getName() == "Oferta");
    assert(repo.repo_findOffer("Oferta").getDestination() == "Cluj");
    assert(repo.repo_findOffer("Oferta").getType() == "Urban");
    assert(repo.repo_findOffer("Oferta").getPrice() == 100);
    Offer off2{"Oferta2", "Suceava", "Rural", 200};
    repo.repo_addOffer(off2);
    assert(repo.repo_findOffer("Oferta2").getName() == "Oferta2");
    assert(repo.repo_findOffer("Oferta2").getDestination() == "Suceava");
    assert(repo.repo_findOffer("Oferta2").getType() == "Rural");
    assert(repo.repo_findOffer("Oferta2").getPrice() == 200);
    try{
        repo.repo_addOffer(off);
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }
    try{
        repo.repo_findOffer("Oferta3");
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }
    repo.repo_deleteOffer(off2);
    try{
        repo.repo_findOffer("Oferta2");
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }
    try{
        repo.repo_deleteOffer(off2);
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }

    vector<Offer> test_Vector = repo.repo_getAll();
    assert(test_Vector.size() == 1);

    std::ostringstream oss;
    RepoException ex("Test message");
    oss << ex;
    assert(oss.str() == "Test message");
}

void test_DynamicVector(){
    DynamicVector vect{};
    IteratorVector it{vect};
    Offer off{"Oferta", "Cluj", "Urban", 100};
    Offer off2{"Oferta2", "Suceava", "Rural", 200};
    Offer off3{"Oferta3", "Suceava", "Rural", 200};
    Offer off4{"Oferta4", "Suceava", "Rural", 200};
    Offer off5{"Oferta5", "Suceava", "Rural", 200};
    Offer off6{"Oferta6", "Suceava", "Rural", 200};

    vect.add(off);
    vect.add(off2);
    assert(vect.get(0).getName() == "Oferta");
    assert(vect.get(1).getPrice() == 200);
    vect.set(0, off2);
    assert(vect.get(1).getName() == "Oferta2");
    assert(vect.len() == 2);
    assert(it.element().getName() == "Oferta2");
    it.next();
    assert(it.element().getPrice() == 200);
    vect.add(off3);
    vect.add(off4);
    vect.add(off5);
    vect.add(off6);
    assert(vect.len() == 6);
    it.next();
    assert(it.element().getName() == "Oferta3");
    it.next();
    assert((*it).getName() == "Oferta4");
    it.next();
    it.next();
    it.next();
    assert(it.valid() == false);
    DynamicVector new_vec{};
    new_vec = vect;
    assert(new_vec.len() == 6);

    DynamicVector original{};
    original.add(off);
    original.add(off2);
    original.add(off3);

    DynamicVector copy{original};

    assert(copy.len() == original.len());




}

void test_Service(){
    OffersRepo rep{};
    OfferValidator val{};
    Service serv{rep, val};
    serv.addOffer("Oferta", "Cluj", "Urban", 100);
    assert(serv.serv_findOffer("Oferta").getName() == "Oferta");
    assert(serv.serv_findOffer("Oferta").getDestination() == "Cluj");
    assert(serv.serv_findOffer("Oferta").getType() == "Urban");
    assert(serv.serv_findOffer("Oferta").getPrice() == 100);
    serv.addOffer("Oferta2", "Suceava", "Rural", 200);
    assert(serv.serv_findOffer("Oferta2").getName() == "Oferta2");
    assert(serv.serv_findOffer("Oferta2").getDestination() == "Suceava");
    assert(serv.serv_findOffer("Oferta2").getType() == "Rural");
    assert(serv.serv_findOffer("Oferta2").getPrice() == 200);
    try{
        serv.addOffer("Oferta", "Cluj", "Urban", 100);
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }
    try{
        serv.serv_findOffer("Oferta3");
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }

    serv.deleteOffer("Oferta");
    try{
        serv.serv_findOffer("Oferta");
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);
    }

    vector<Offer> test_Vector = serv.serv_getAll();
    assert(test_Vector.size() == 1);
    serv.addOffer("Oferta", "Cluj", "Urban", 100);
    serv.addOffer("Oferta4", "Suceava", "Rural", 200);
    vector<Offer> test_Vector2 = serv.serv_getFiltered("destination", "Cluj");
    assert(test_Vector2.size() == 1);
    vector<Offer> test_Vector3 = serv.serv_getFiltered("price", "100");
    assert(test_Vector3.size() == 1);
    serv.serv_modifyOffer("Oferta", "Oferta3", "Cluj", "Urban", 100);
    assert(serv.serv_findOffer("Oferta3").getName() == "Oferta3");
    assert(serv.serv_findOffer("Oferta3").getDestination() == "Cluj");
    assert(serv.serv_findOffer("Oferta3").getType() == "Urban");
    assert(serv.serv_findOffer("Oferta3").getPrice() == 100);


    vector<Offer> test_Vector4 = serv.sortByName();
    assert(test_Vector4.size() == 3);


    vector<Offer> test_Vector5 = serv.sortByDestination();
    assert(test_Vector5.size() == 3);


    vector<Offer> test_Vector6 = serv.sortByType();
    assert(test_Vector6.size() == 3);


    vector<Offer> test_Vector7 = serv.sortByPrice();
    assert(test_Vector7.size() == 3);

    vector<Offer> test_Vector8 = serv.serv_filterByDestinationWithCopyIf("Cluj");
    assert(test_Vector8.size() == 1);

    vector<Offer> test_Vector9 = serv.serv_filterByPriceWithCopyIf(100);
    assert(test_Vector9.size() == 1);

    serv.addWishlist("Oferta3");
    vector<Offer> test_Vector10 = serv.getWishlist();
    assert(test_Vector10.size() == 1);

    serv.emptyWishlist();
    vector<Offer> test_Vector11 = serv.getWishlist();
    assert(test_Vector11.size() == 0);

    serv.addWishlist("Oferta3");
    vector<Offer> test_Vector12 = serv.getWishlist();
    assert(test_Vector10.size() == 1);

    serv.exportWishlist("/Users/dangaspar/Documents/CS-UBB/Year01/Structuri de date si algoritmi/Laboratoare/LaboratorQT/testoutput.txt");
    int count;
    std::ifstream file("/Users/dangaspar/Documents/CS-UBB/Year01/Structuri de date si algoritmi/Laboratoare/LaboratorQT/testoutput.txt");
    count = 0;
    std::string line;
    while (std::getline(file, line)){
        count++;
    }
    assert(count == 3);

    serv.generateWishlist(2);
    vector<Offer> test_Vector13 = serv.getWishlist();
    assert(test_Vector13.size() == 3);

    vector<Offer> test_Vector14 = serv.serv_getAll();
    assert(test_Vector14.size() == 3);
    serv.addOffer("Oferta5", "Cluj", "Urban", 100);
    serv.undo();

    serv.addOffer("Oferta5", "Cluj", "Urban", 100);
    serv.deleteOffer("Oferta5");
    serv.undo();

    serv.serv_modifyOffer("Oferta5", "Oferta6", "Cluj", "Urban", 100);
    serv.undo();

}

void test_FileRepository(){

    FileRepository fileRepo2{"/Users/dangaspar/Documents/CS-UBB/Year01/Structuri de date si algoritmi/Laboratoare/LaboratorQT/testoutput2.txt"};

    std::ofstream ofs;
    ofs.open("/Users/dangaspar/Documents/CS-UBB/Year01/Structuri de date si algoritmi/Laboratoare/LaboratorQT/testoutput2.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    FileRepository fileRepo{"/Users/dangaspar/Documents/CS-UBB/Year01/Structuri de date si algoritmi/Laboratoare/LaboratorQT/testoutput2.txt"};
    Offer off{"Oferta", "Cluj", "Urban", 100};
    Offer off2{"Oferta2", "Suceava", "Rural", 200};
    Offer off3{"Oferta3", "Suceava", "Rural", 200};

    fileRepo.repo_addOffer(off);
    fileRepo.repo_addOffer(off2);
    fileRepo.repo_addOffer(off3);
    vector<Offer> test_Vector = fileRepo.repo_getAll();
    assert(test_Vector.size() == 3);

    fileRepo.repo_deleteOffer(off);
    vector<Offer> test_Vector2 = fileRepo.repo_getAll();
    assert(test_Vector2.size() == 2);


    try {
        fileRepo.repo_deleteOffer(off);
        assert(false);
    }
    catch (RepoException &ex){
        assert(true);

    }
}


void testAll(){
    test_Offer();
    test_Validator();
    test_Repository();
    test_Service();
    test_DynamicVector();
    test_FileRepository();
}

