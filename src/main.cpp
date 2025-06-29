#include "global_stuff.hpp"
#include "utms.hpp"
#include "../server/server.hpp"
#include "handlers.hpp"

void mapServerPaths(Server& server, System *system)
{
    Server *server_ptr = &server;

    server.setNotFoundErrPage("static/404.html");

    server.get("/", new ShowPage("static/home.html"));

    server.get("/images/defualt_profile.png", new ShowImage("images/defualt_profile.png"));

    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(system));

    server.get("/logout", new LogoutHandler(system));

    server.get("/mainpage", new MainPageHandler("template/main_page.html", system));

    server.get("/profile_photo", new ShowPage("static/profile_photo.html"));
    server.post("/profile_photo", new ProfileChangeHandler(system, server_ptr));

    server.get("/send_post", new ShowPage("static/send_post.html"));
    server.post("/send_post", new SendPostHandler(system, server_ptr));

    server.get("/personal_page", new PersonalPageHandler("template/personal_page.html", system));

    server.get("/search_user", new ShowPage("static/search_user.html"));
    server.post("/search_user", new SearchUserHandler(system));

    server.get("/take_course", new ShowPage("static/take_course.html"));
    server.post("/take_course", new TakeCourseHandler(system));

    server.get("/remove_course", new ShowPage("static/remove_course.html"));
    server.post("/remove_course", new RemoveCourseHandler(system));

    server.get("/view_taken_courses", new ViewTakenCoursesHandler("template/view_courses.html", system));

    server.get("/offer_course", new ShowPage("static/offer_course.html"));
    server.post("/offer_course", new OfferCourseHandler(system));

    server.get("/view_courses", new ViewCoursesHandler("template/view_courses.html", system));
}

int main(int argc, char *argv[])
{
    try
    {
        int port = 5000;
        Server server(port);
        System* system = new System(argv[1], argv[2], argv[3], argv[4]);
        mapServerPaths(server, system);
        cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument& e)
    {
        cerr << e.what() << endl;
    }
    catch (const Server::Exception& e)
    {
        cerr << e.getMessage() << endl;
    }
}