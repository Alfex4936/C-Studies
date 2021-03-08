import ssl

from urllib.error import HTTPError, URLError
from urllib.request import urlopen

from selectolax.parser import HTMLParser


class AjouException(Exception):
    __module__ = Exception.__module__

    def __init__(self, msg="Exception!"):
        self.msg = msg
        super().__init__(self.msg)


class Ajou:
    __slots__ = ("notices",)

    def __init__(self):
        self.notices = []

    def __len__(self):
        return len(self.notices)

    @staticmethod
    def getHTML(url=None):
        if url is None:
            raise AjouException("Please enter URL to get HTML contents")
        context = ssl._create_unverified_context()
        try:
            result = urlopen(url, timeout=5.0, context=context)
        except HTTPError:
            print("Seems like the server is down now.")
            return None
        except TimeoutError:
            print("It's taking too long to load website.")
            return None
        except URLError:
            print("Wrong url to parse")
            return None

        html = result.read().decode("utf-8")
        return html

    def parse(self, limit=None):
        ADDRESS = "https://www.ajou.ac.kr/kr/ajou/notice.do"
        if limit is None:
            limit = 30
        url = f"{ADDRESS}?mode=list&articleLimit={limit}&article.offset=0"

        """공지 파서 메인

        Args:
            url (str, optional): 홈페이지 URL (with admin options). Defaults to None.
            length (int, optional): 몇 개의 공지를 읽을 것인가. Defaults to 10.

        Returns:
            ids, posts, dates, writers, length (list, optional): length에 따른 공지 목록을 전부 불러온다.
        """

        context = ssl._create_unverified_context()
        try:
            result = urlopen(url, timeout=2.0, context=context)
        except HTTPError:
            print("Seems like the server is down now.")
            return None, 0  # make entity
        except TimeoutError:
            print("It's taking too long to load website.")
            return None, 0  # make entity

        html = result.read().decode("utf-8")
        soup = HTMLParser(html)
        no_post = soup.css_first("td.b-no-post")
        if no_post:
            return None, 0  # make entity

        ids = soup.css("td.b-num-box")
        posts = soup.css("div.b-title-box > a")
        # links will be generated by posts[i] href
        dates = soup.css("span.b-date")
        writers = soup.css("span.b-writer")
        length = len(ids)

        ids = soup.css("td.b-num-box")
        posts = soup.css("div.b-title-box > a")
        dates = soup.css("span.b-date")
        writers = soup.css("span.b-writer")

        notices = [
            Notice(
                ids[i].text(strip=True),
                posts[i].text(strip=True),
                dates[i].text(strip=True),
                writers[i].text(strip=False),
                ADDRESS + posts[i].attributes["href"],
            )
            for i in range(length)
        ]  # memory

        self.notices = notices

        return notices, length

    def print(self):
        if not self:
            raise AjouException("Please run parse() before print()")
        for i in range(len(self)):
            print("ID:", self.notices[i].id)
            print("Title:", self.notices[i].title)
            print("Posted date:", self.notices[i].date)
            print("Writer:", self.notices[i].writer)
            print("Link:", self.notices[i].link[51:])


class Notice:
    ADDRESS = "https://www.ajou.ac.kr/kr/ajou/notice.do"

    __slots__ = ("_id", "_post", "_date", "_link", "_writer", "_link")

    def __init__(self, id, post, date, writer, link):
        self._id = id
        self._post = post
        self._date = date
        self._writer = writer
        self._link = link

    @property
    def id(self):
        return self._id

    @id.setter
    def id(self, id):
        self._id = id

    @property
    def title(self):
        return self._post

    @title.setter
    def title(self, title):
        self._post = title

    @property
    def date(self):
        return self._date

    @date.setter
    def date(self, date):
        self._date = date

    @property
    def writer(self):
        return self._writer

    @writer.setter
    def writer(self, writer):
        self._writer = writer

    @property
    def link(self):
        return self._link

    @link.setter
    def link(self, link):
        self._link = link


if __name__ == "__main__":
    ajou = Ajou()
    ajou.getHTML("https://www.programiz.com/python-programming/user-defined-exception")
